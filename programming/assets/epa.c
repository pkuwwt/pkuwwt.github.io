
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct Point {
    double lon;
    double lat;
} Point;

typedef struct PointList {
    int length;
    Point* data;
} PointList;

typedef struct IntList {
    int length;
    int* data;
} IntList;

IntList init_int_list(int N) {
    IntList list;
    list.length = N;
    list.data = (int*)malloc(sizeof(int) * N);
    return list;
}

void print_int_list(IntList arr) {
    for (int i=0;i<arr.length; ++i) {
        printf("%d,", arr.data[i]);
    }
    printf("\n");
}

void free_int_list(IntList arr) {
    if (arr.data != NULL) {
        free(arr.data);
        arr.length = 0;
        arr.data = NULL;
    }
}

PointList init_point_list(int N) {
    PointList list;
    list.length = N;
	if (N > 0) {
		list.data = (Point*) malloc(sizeof(Point) * N);
	} else {
		list.data = NULL;
	}
    return list;
}

PointList create_point_list(int N, ...) {
    va_list args;
    PointList list = init_point_list(N);
    Point point;
    va_start(args, N);
    for (int i=0; i<N*2; ++i) {
        double value = va_arg(args, double);
        if (i % 2 == 0) {
            point.lon = value;
        } else {
            point.lat = value;
            list.data[i / 2] = point;
        }
    }
    va_end(args);
    return list;
}

void print_point_list(PointList points) {
	for(int i=0; i<points.length; ++i) {
		printf("%f %f;", points.data[i].lon, points.data[i].lat);
	}
	if (points.length > 0) {
		printf("\n");
	}
}

void free_point_list(PointList points) {
    if (points.data != NULL) {
        free(points.data);
        points.length = 0;
        points.data = NULL;
    }
}

int binary(int value) {
    if (value < 0) {
        return ~(((~(-value)) + 1) << 1);
    } else {
        return value << 1;
    }
}

int numberOfLeadingZeros(int value) {
    int count = 32;
    while (value != 0) {
        count--;
        value = value >> 1;
    }
    return count;
}

IntList five_bits(int value) {
    int lenBits = 32 - numberOfLeadingZeros(value);
    int length = (int)(lenBits * 0.2 + 0.99);
    IntList result = init_int_list(length);
    int mask = 0x1F;   //  11111
    int offset = 0x3F; // 111111
    for (int i=0; i<length; ++i) {
        if (i == length - 1) {
            result.data[i] = (value & mask) + offset;
        } else {
            result.data[i] = ((value & mask) | 0x20) + offset;
        }
        value = value >> 5;
    }
    return result;
}

char* ascii(IntList values) {
    char* str = (char*) malloc(values.length + 1);
    for (int i=0; i<values.length; ++i) {
        str[i] = (char)values.data[i];
    }
    str[values.length] = '\0';
    free_int_list(values);
    return str;
}

// assume value >= 0
// multiply with 100000, and round it
int quantify(double value) {
    value = value * 100000;
    if (value > 0) {
        return (int)(value + 0.5);
    } else {
        return -(int)(-value + 0.5);
    }
}

char* convert(double value) {
	printf("%f\n", value);
    return ascii(five_bits(binary(quantify(value))));
}

char* epa_encode(PointList points) {
    char* buffer = (char*)malloc(sizeof(char) * points.length * 10);
    int length = 0;
    for (int i=0;i<points.length; ++i) {
        double diffLat, diffLon;
        if (i == 0) {
            diffLat = points.data[i].lat;
            diffLon = points.data[i].lon;
        } else {
            diffLat = points.data[i].lat - points.data[i-1].lat;
            diffLon = points.data[i].lon - points.data[i-1].lon;
        }
        char* latStr = convert(diffLat);
        char* lonStr = convert(diffLon);
        strcpy(buffer + length, latStr);
        length += (int)strlen(latStr);
        strcpy(buffer + length, lonStr);
        length += (int)strlen(lonStr);
        free(latStr);
        free(lonStr);
    }
    buffer[length] = '\0';
    return buffer;
}

PointList epa_decode(const char* s) {
	if (s == NULL) {
		return init_point_list(0);
	}
	int length = strlen(s);
	int index = 0;
	int currentLat = 0;
	int currentLng = 0;
	int next5bits;
	int sum;
	int shifter;
	PointList buffer = init_point_list(length / 2);
	int nPoints = 0;
	while (index < length) {
		// calculate next latitude
		sum = 0;
		shifter = 0;
		do {
			next5bits = (int)s[index++] - 63;
			sum |= (next5bits & 31) << shifter;
			shifter += 5;
		} while (next5bits >= 32 && index < length);

		if (index >= length) {
			break;
		}

		currentLat += (sum & 1) == 1 ? ~(sum >> 1) : (sum >> 1);

		//calculate next longitude
		sum = 0;
		shifter = 0;
		do {
			next5bits = (int)s[index++] - 63;
			sum |= (next5bits & 31) << shifter;
			shifter += 5;
		} while (next5bits >= 32 && index < length);

		if (index >= length && next5bits >= 32) {
			break;
		}

		currentLng += (sum & 1) == 1 ? ~(sum >> 1) : (sum >> 1);

		Point point;
		point.lon = currentLng * 0.00001;
		point.lat = currentLat * 0.00001;
		buffer.data[nPoints++] = point;
	}
	PointList result = init_point_list(nPoints);
	memcpy(result.data, buffer.data, sizeof(Point) * nPoints);
	free_point_list(buffer);
	return result;
}


int main(int argc, char* argv[]){
	PointList points = create_point_list(
			3,
			-120.2, 38.5,
			-120.95, 40.7,
			-126.453, 43.252
			);
	char* output = epa_encode(points);
	printf("%s\n", output);
	PointList points2 = epa_decode(output);
	print_point_list(points2);
	free_point_list(points2);
	free(output);
	free_point_list(points);
	return 0;
}

