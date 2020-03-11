---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
title: Encoded Polyline Algorithm
---

## What is EPA (Encoded Polyline Algorithm)

[EPA (Encoded Polyline Algorithm)](https://developers.google.com/maps/documentation/utilities/polylinealgorithm) is an
algorithm to encode a polyline to a string. For example, the following series of points

```
[[38.5, -120.2], [40.7, -120.95], [43.252, -126.453]]
```

can be encoded as

```
_p~iF~ps|U_ulLnnqC_mqNvxq`@
```

## How EPA works?

EPA encoder can be describe as

  * `encode(x1,y1,x2,y2,...) => convert(x1) + convert(y1) + convert(x2-x1) + convert(y2-y1) + ...`
  * `convert(v) = ascii(five_bits(binary(quantize(v))))`
  * `quantize`: multiply a float value with 100000, and round to int
  * `binary`: encode an integer to bits
  * `five_bits`: divide the bits to groups, each group has 5 bits
  * `ascii`: encode 5 bits to a char

## Implementation
  
  * [mapbox/polyline](https://github.com/mapbox/polyline)
  * [EPA in C](../assets/epa.c)
  * [EPA in GO](../assets/epa.go)
  * [EPA in Python](../assets/epa.py)

