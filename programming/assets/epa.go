package main

import "fmt"
import "strings"

type Point struct {
    lon float64
    lat float64
}

func ascii(values []int) string {
    if (values == nil) {
        return "";
    }
    chars := make([]string, len(values))
    for i, v := range values {
        chars[i] = string(v)
    }
    return strings.Join(chars, "")
}

func number_of_leading_zeros(value int) int {
    count := 32
    for (value != 0) {
        count = count - 1
        value = value >> 1
    }
    return count
}

func five_bits(value int) []int{
    lenBits := 32 - number_of_leading_zeros(value)
    length := (int)(float64(lenBits) * 0.2 + 0.99)
    mask := 0x1F
    offset := 0x3F
    result := []int{}
    for i:=0; i<length; i++ {
        if i == length - 1 {
            result = append(result, (value & mask) + offset)
        } else {
            result = append(result, ((value & mask) | 0x20) + offset)
        }
        value = value >> 5
    }
    return result
}

func binary(value int) int {
    if (value < 0) {
        return ^(((^(-value)) + 1) << 1)
    } else {
        return value << 1
    }
}

func quantify(value float64) int {
    if (value > 0) {
        return (int)(value * 100000 + 0.5)
    } else {
        return -(int)(-value * 100000 + 0.5)
    }
}

func convert(value float64) string {
    return ascii(five_bits(binary(quantify(value))))
}

func epa_encode(points []Point) string {
    if (points == nil) {
        return ""
    }
    var result = ""
    for i, point := range points {
        if (i == 0) {
            result += convert(point.lat)
            result += convert(point.lon)
        } else {
            result += convert(point.lat - points[i-1].lat)
            result += convert(point.lon - points[i-1].lon)
        }
    }
    return result
}

func decode_bytes(index int, encoded string) [3]int {
    length := len(encoded)
    sum := 0
    shifter := 0
    next5bits := encoded[index] - 63
    index = index + 1
    sum |= (int(next5bits) & 31) << shifter
    shifter += 5
    for (next5bits >= 32 && index < length) {
        next5bits = encoded[index] - 63
        index = index + 1
        sum |= (int(next5bits) & 31) << shifter
        shifter += 5
    }
    return [3]int{sum,index,int(next5bits)}
}

func epa_decode(encoded string) []Point {
    length := len(encoded)
    currentLat := 0
    currentLng := 0
    points := []Point{}
    index := 0
    for (index < length) {
        tuple := decode_bytes(index, encoded)
        sum := tuple[0]
        index = tuple[1]
        if (index >= length) {
            break
        }
        if ((sum & 1) == 1) {
            currentLat += ^(sum >> 1)
        } else {
            currentLat += (sum >> 1)
        }
        tuple = decode_bytes(index, encoded)
        sum = tuple[0]
        index = tuple[1]
        next5bits := tuple[2]
        if (index >= length && next5bits >= 32) {
            break
        }
        if ((sum & 1) == 1) {
            currentLng += ^(sum >> 1)
        } else {
            currentLng += (sum >> 1)
        }
        point := Point{lon: float64(currentLng) * 0.00001, lat: float64(currentLat) * 0.00001}
        points = append(points, point)
    }
    return points
}

func main() {
    points := []Point{
        Point{lon:-120.2, lat:38.5},
        Point{lon:-120.95, lat:40.7},
        Point{lon:-126.453, lat:43.252},
    }
    result_ref := "_p~iF~ps|U_ulLnnqC_mqNvxq`@"
    fmt.Println(epa_encode(points))
    fmt.Println(epa_encode(points) == result_ref)
    points1 := epa_decode(result_ref)
    fmt.Println(points1)
}

