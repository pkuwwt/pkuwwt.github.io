---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
tags: java, functional programming
title: Functional programming in Java
---

## Build-in functional functions

The most frequently used generic functions are as follows:

  * `Runnable`: a piece of code without exceptions
  * `Callable`: a piece of code that may throws exceptions
  * `Function<S,T>`: convert instance of type `S` to instance of type `T`
  * `Supplier<T>`: provide result of type `T`
  * `Consumer<T>`: accept input of type `T`
  * `BiFunction<T,U,R>`: accept inputs of type `T` and `U`, return instance of `R`
  * `Preciate<T>`: judge if input of `T` is true or not

With all these functions, why should we define something like `OnClickListener`?

The only reason we want to define an single-method interface is that we need it to be distinguishable from others.

## Lambda

### Lambda for single-method interface

For an interface with exactly one method
````
interface OnClickListener {
	void click(View v);
}
```
we can always use lambda function to represent its instances. For example, the following calls are equivalent:

```
OnClickListener listener1 = new OnClickListener() {
	void click(View v) {
		System.out.println('click me');
	}
};
OnClickListener listener2 = v -> System.out.println('click me');
view.setOnClickListener(listener1)
view.setOnClickListener(listener2)
view.setOnClickListener(v -> System.out.println('click me'))
```

The benefit of the 3rd usage is that we don't need to import `OnClickListener`, and we don't event need to know its existence when programming.

The benefit of the 2nd usage is that sometimes we need to figure out what happens when the functional-styled code is too compact.

You won't want to use 1st usage any more.

### Lambda for method reference

Method references are useful to convert methods of instances or classes to lambda functions.

We can reference the static method
```java
class View {
	public static View inflate(Context context, int resource, ViewGroup root) {}
}
```
as `View::inflate`.

We can reference a method of an instance
```java
class Activity {
	public void finish() {}
}
Activity activity = new Activity();
Consumer<Activity> method = activity::finish;
```
The instance itself is the first argument of the lambda function.

### `Void` type

`Void` is just a placeholder for `void`-return for empty-arguments. Its constructor is private, and only accepts `null`.

Sometimes we cannot use `Consumer<Integer>` for a 3rd-party api, but `Function<Integer, Void>`.

## CompletableFuture

`Future` paradigm is capable of representing the semantics of delay.

There is a sample

```
Supplier<Integer> getNumber = () -> {
	try {
		Thread.sleep(1000);
		return 1;
	} catch (Exception e) {
		return 0;
	}
};
CompletableFuture<Integer> number = new CompletableFuture<>();
(new Thread() {
	public void run() {
		number.complete(getNumber.get());
	}
}).start();
number.thenAcceptAsync(System.out::println);
```
We should notice that the thread in `thenAcceptAsync` may not be the thread before it.

## Optional

`Optional` type is useful to avoid code like
```
Result result = generateResult();
Property property = null;
if (result != null) {
	property = result.getProperty();
}
```
We can rewrite it as
```
Property property = Optional.ofNullable(generateResult())
	.map(Result::getProperty)
	.orElse(null);
```

## map, filter and reduce

Java collections provide stream api, which has fully functional abilities.

For example, we can multiple integers as follows
```java
List<Integer> numbers = Arrays.of(1, 2, 3);
List<Integer> multiplies = numbers.stream().map(i -> i * 2).collect(Collecors.toList());
multiplies.forEach(System.out::println);
```

We can filter all even numbers
```java
List<Integer> numbers = Arrays.of(1, 2, 3);
List<Integer> evens = numbers.stream().filter(i -> i % 2 == 0).collect(Collecors.toList());
```

We can sum the numbers
```java
List<Integer> numbers = Arrays.of(1, 2, 3);
Integer sum = numbers.stream().reduce(0, Integer::sum);
```

