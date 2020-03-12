from typing import List

class Point:
    def __init__(self, lon, lat):
        self.lon = lon
        self.lat = lat
    def __str__(self):
        return '{} {}'.format(self.lon, self.lat)

def quantify(number: float) -> int:
    if number > 0:
        return (int)(number * 100000 + 0.5)
    else:
        return -(int)(-number * 100000 + 0.5)

def binary(value: int) -> int:
    if value < 0:
        return ~(((~(-value)) + 1) << 1)
    else:
        return value << 1

def number_of_leading_zeros(value: int) -> int:
    count = 32
    while value != 0:
        count = count - 1
        value = value >> 1
    return count

def five_bits(value: int) -> List[int]:
    lenBits = 32 - number_of_leading_zeros(value)
    length = int(lenBits * 0.2 + 0.99)
    mask = 0x1F
    offset = 0x3F
    result = []
    for i in range(length):
        if i == length - 1:
            result.append((value & mask) + offset)
        else:
            result.append(((value & mask) | 0x20) + offset)
        value = value >> 5
    return result

def ascii(values: List[int]) -> str:
    return ''.join(chr(i) for i in values)

def convert(number: float):
    return ascii(five_bits(binary(quantify(number))))

def epa_encode(points: List[Point]) -> str:
    res:str = ''
    lastPoint = None
    for point in points:
        if lastPoint == None:
            res += convert(point.lat)
            res += convert(point.lon)
        else:
            res += convert(point.lat - lastPoint.lat)
            res += convert(point.lon - lastPoint.lon)
        lastPoint = point
    return res

def epa_decode(encoded: str) -> List[Point]:
    if encoded == None:
        return None
    length = len(encoded)
    currentLat = 0
    currentLng = 0
    points = []
    index = 0
    while index < length:
        # calculate next latitude
        def decode_bytes(index, encoded):
            sum = 0
            shifter = 0
            next5bits = ord(encoded[index]) - 63
            index = index + 1
            sum |= (next5bits & 31) << shifter
            shifter += 5
            while next5bits >= 32 and index < length:
                next5bits = ord(encoded[index]) - 63
                index = index + 1
                sum |= (next5bits & 31) << shifter
                shifter += 5
            return sum,index,next5bits
        sum,index,_ = decode_bytes(index, encoded)
        if index >= length:
            break
        currentLat += (~(sum >> 1) if (sum & 1) == 1 else (sum >> 1))
        sum,index,next5bits = decode_bytes(index, encoded)
        if index >= length and next5bits >= 32:
            break
        currentLng += (~(sum >> 1) if (sum & 1) == 1 else (sum >> 1))
        points.append(Point(currentLng * 0.00001, currentLat * 0.00001))
    return points

def plot_line(points):
    import matplotlib.pyplot as plt
    x = [p.lon for p in points]
    y = [p.lat for p in points]
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    points = [
            Point(-120.2, 38.5),
            Point(-120.95, 40.7),
            Point(-126.453, 43.252)
            ]
    result_ref = "_p~iF~ps|U_ulLnnqC_mqNvxq`@"
    result = epa_encode(points)
    print(result)
    print(result_ref == result)
    print(';'.join([str(p) for p in epa_decode(result_ref)]))

