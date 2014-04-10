# intro to circuits lesson 3
all about transistors (and some other stuff)

## potentiometers (the other stuff)

### voltage dividers
Consider the following circuit:

![voltage divider circuit](3-1_voltage-divider_schem.png "i wonder why it's called a voltage divider")

It's pretty simple: two resistors in series, and we're measuring the voltage level between them (or, in other words, the voltage across the bottom resistor). What will that voltage be?

![voltage divider math](equations/voltage-divider-math.png "mmm, mathy")

Hey, look, that voltage looks to be around 9/10 of the starting voltage (in actuallity, it's 10/11 of 5V). Let's take our math from above and generalize it a little:

![general voltage divider math](equations/voltage-divider-general.png "mmm, generalized")

In a voltage divider, the voltage level in between the two resistors is equal to the input voltage times the ratio of the second resistor to the sum of both resistors.

Verify this by building this circuit with one resistor changed and running that calculation.

![another voltage divider](3-1b_voltage-divider_schem.png "notice the different value for R1")

You should see a voltage of around 3.8V on your voltmeter.

How does this help us? In the course of... this course, we will ocasionally need a reference voltage of some sort. Since the only source we have is 5V, we need a way to get all the voltages in between.

### what is a potentiometer and how does it fit into all of this
So, without further ado, let's get to potentiometers. This is the symbol for a "pot" (as they will be called from now on).

 