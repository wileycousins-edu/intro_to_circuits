# intro to circuits - transistors (the fun stuff)
Transitioning into puns that are even worse than before.

## what is a transistor?
Transistors are the backbone of our digital world. There are millions of them in the computer you're on right now. I've given you twenty. They look a lot like this:

![transistor](images/transistors.jpg)

A transistor is like a valve controlling water flow, except it controls current flow. It can be closed, partially open, or fully open.

## types of transistors
The transistors that you have are called bi-polar junction transistors, or BJTs. They are so-called because they rely on a sandwich of two types of semiconductors. If you care about any of this, I highly recommend [the wikipedia page](http://en.wikipedia.org/wiki/Bipolar_junction_transistor).

The semiconductors are referred to as N-type and P-type. Because the BJT is a sandwich of these two materials, there are two possible configurations: NPN and PNP. We will start off with NPN BJTs.

Another important type of transistor is the FET (field-effect transistor). We will not use them in this course, but please know that they both exist and operate differently than BJTs.

## NPN BJTs
You have five NPN transistors with the model number **2N3904**. You can see this written in very small letters on the flat face of the transistor. Every transistor with the same model number has the same specifications, and you can use the model number to find those specs.

![npn transistor](images/npn-transistor.jpg)

The symbol for an NPN transistor is this:

![npn byt symbol][npn-bjt_sym]

The E, B, and C stand for Emitter, Base, and Collector, respectively. Where do those names come from? Who cares? I forget. Probably something about holes and electrons. [You might be able to find out here](http://en.wikipedia.org/wiki/Bipolar_junction_transistor). Regardless of all that, **take note of the arrow on the emitter pin and the direction (outwards) that it's pointing.**

Do you remember that time I told you that transistors are like valves? It's still true. The current that an NPN transistor valve controls is the **current flowing between the collector and the emitter.**

What determines how "open" the "valve" is? The current flowing into the base. More specifically:

![i_CE = h_FE * i_BE][trans-eq]

Where i_CE is the current flowing from the collector to emitter, i_BE is the current flowing into the base (and out the emitter), and h_FE is the gain of the transistor. The gain is a property of the transistor and is usually around 100.

**A little bit of current flowing into the base allows a lot of current to flow into the collector**. Both of those currents flow out of the emitter.

## datasheets

Where do we find the gain (and other properties of the transistor)? From the **datasheet**. Datasheets are big sheets of data about specific parts (all components, not just transistors). You find them by googling the part number and then clicking the first PDF link you see. Try it now with your NPN BJT part number (2N3904).

You'll hopefully find [something like this](http://www.fairchildsemi.com/ds/2N/2N3904.pdf).

This document looks pretty daunting! Don't worry, I have a trick. **If you see something you don't understand, ignore it.** Eventually, you'll need more bits of information, and you'll learn about them specifically then. The way to get good at reading datasheets is to read a lot of datasheets. And the way to read a lot of datasheets is to not get overwhelmed by all the data.

**The single most important piece of data on a datasheet is the pinout**. Your device has a schematic diagram and a physical package. The pinout is what relates the diagram to real life. Find where the datasheet tells you which of the transistor's legs correspond to the emitter, base, and collector.

![bjt pinout][bjt-pinout]

When looking at the flat side of the BJT (the side with the model number printed on it), the left leg is the emitter, the middle leg is the base, and the right leg is the collector.

**Skim through your datasheet and see if you can find the gain for your transistor.** You'll find several numbers in a table, all corresponding to different "test conditions". You can use these test conditions to decide what the gain is likely to be for a circuit you design.

![2n3904 gain](images/2n3904-datasheet-gain.png "page 2 of the datasheet")

Source: http://www.fairchildsemi.com/ds/2N/2N3904.pdf

For simplicity's sake, at the moment we're gonna assume the gain is always 100. This assumption turns out to work a lot of the time, for a lot of transistors, but it isn't always true.

## using an NPN transistor
To use your transistor, you need to start with one question: how much current does my device need? In our first transistor circuit, our device, or load, will be an LED. So, **let's say our load is 20mA**.

Our transistor is a current valve, so it goes in series with our load. That means whatever current is flowing through our device is flowing through our transistor (from C to E in an NPN).

![npn bjt symbol][npn-bjt_sym]

The transistor's operation is governed by the equation ![i_CE = h_FE * i_BE][trans-eq], so knowing that the CE junction is in series with our LED, the LED current is 20mA, and the gain of our transistor is 100, we can start building our circuit.

Applying the transistor equation gives us **i_BE = 0.2mA** (20mA / 100). This means that for our valve to be open enough to light our LED with the current we want (20mA), we need to ensure that 0.2mA flows through the base-emitter junction.

### the junctions
It's important to note that a BJT is effectively a diode sandwich. And diodes tend to drop about the same voltage no matter the current. In a BJT, there are two voltage drops we care about: the CE junction voltage drop, and the BE junction voltage drop. They are abbreviated v_CE, and v_BE.

![npn bjt voltage drops][npn-bjt_volts]

In red is v_BE, and in green is v_CE. Looking back at the data sheet, you'll notice that in "ON CHARACTERISTICS", underneath the gain, it gives you some values for v_BE and v_CE (ignore the "SAT" for now). Notice that v_CE is much smaller than v_BE.

To turn the transistor on, current has to flow from the base to the emitter. For that to happen, the base has to be at a high voltage level than the emitter (current flows from high voltage to low voltage). How much higher? High enough to satisfy the voltage drop needed by the BE junction.

### high side vs low side

With a switch in series with a load, we can put it either before the load (high-side) or after the load (low side). In this circuit, our load is a 1kΩ resistor, S1 is the high-side switch, and S2 is the low-side switch:

![high-side and low-side][high-low]

High side / low side doesn't really matter with a push button, but does it matter with a transistor? The short answer is yes, it does. And the why has to do with those junction voltage drops.

### NPNs are low-side switches
Current flows from collector to emitter in an NPN, so let's imagine a NPN wired up as a high side switch. The collector would be hooked up to 5V, and the emitter would be hooked up to the load, which would then be hooked to ground.

If we wanted to turn this NPN on, we'd need to get current flowing into the base and out the emitter. If C is at 5V, then E is going to be at (5V - v_CE). To get current to flow, B is going to have to be v_BE higher than E. But, v_BE is several times greater than v_CE! So, we need B to be at (5V - v_CE) + v_BE. With v_BE > v_CE, this puts us at a number greater than 5V, which we can't do (without a charge pump circuit).

So, this leaves us with no choice but to put the NPN at the low side of the circuit, with 5V hooked to the load, the load hooked to C, and E hooked to ground. With E at 0V, we now need to pull B to way less than 5V to get current to flow, which we can definitely do.

![npn low side][npn-low]

## saturating a transistor
More often than not, we will use transistors as switches. In this sort of application, we need to ensure that the transistor is open enough to allow more current to flow than our load requires. If the transistor is more open than it needs to be, we call it "saturated".

Saturation can get a little complicated, and involves electrons, holes, and graphs. For all intents and purposes (or at least our intents and purposes), though, a transistor is saturated when an increase in base current does not lead to an increase in collector current.

## biasing a transistor for saturation
Because BJTs operate by amplifying the base current by the gain, we need a way of regulating the base current. As we always do when trying to control current, we will use resistors to accomplish the task. Controlling the currents and voltages going into / across the transistor is called "transistor biasing".

A transistor circuit needs one or two resistors to work properly. For an NPN, that circuit looks like this:

![npn circuit in progress][tr_1_in-progress]

Our biasing resistors are R1 and R2. R_LED is part of the load. For the moment, we are going to pretend that R2 doesn't exist.

![npn circuit sans R2][tr_1_sans-r2]

First off, what's with that button hooked to 5V plugged into the transistor? Couldn't we just use the button with the LED, lose the transistor entirely, and be fine? Yes, we could. Transistors come in handy when you need more current than a button can handle (>50mA) or you have a more complex circuit than a single LED. This is a stupid circuit that is needlessly complex for turning on an LED. But it is exactly complex enough to teach how a NPN BJT works, which is what it's really supposed to do. The button is just our way of giving the BJT a signal to turn on.

There is a simple, step by step procedure to follow to bias your transistor.

### step 1 - determine your necessary base current
You need two pieces of information for this step: your load current and your transistor's gain at that current.

For us, the **load current is 20mA** for our LED, and **the gain at 20mA is about 100** (h_FE from the datasheet). We set our load current equal to i_CE and apply the transistor equation ![i_CE = h_FE * i_BE][trans-eq]. This gives us **i_BE = 0.2mA**.

We then add 25% to that value to be safe. This isn't strictly necessary, but I always do it to ensure saturation. So, **i_BE(sat) = 0.25mA**.

### step 2 - determine the voltage drop across your biasing resistor
When S1 is pushed down, voltage is going to drop from 5V first across R1, and then across the base-emitter junction of Q1. So, **5V = v_R1 + v_BE**. We get v_BE from the datasheet to be somewhere between 0.65 and 0.85 when i_C is 20mA. So, we're going to split the difference and call **v_BE(sat) = 0.75V**.

Plugging those numbers in, we get **v_R1 = 5V - 0.75V = 4.25V**.

### step 3 - apply Ohm's law and select your resistance
Because R1 is in series with the base-emitter junction, **i_BE is going to equal i_R1**. Plugging this fact and the numbers from step 1 and step 2 into Ohm's law gives us i_R1 = i_BE = 0.25mA = v_R1/R1 = 4.25V/R1. Rearranging and sovling for R1 gives us:

**R1 = 4.25V/0.25mA = 17kΩ**.

Now, you take that number, and select the closest resistor you have to that number that is not greater. So, for us, **we'd select a 10kΩ resistor**. Try it out:

#### circuit tr 1

[example breadboard][tr_1_bb]

![circuit tr 1][tr_1_schem]

## a smarter transistor circuit
Remember earlier when we decided to ignore R2? Well, strictly speaking R2 is optional. That being said, especially when using a transistor as a switch, adding R2 in greatly improves switching times (how quickly the transistor shuts off after the signal is removed). This is a desisred behavior. So what is R2 doing and how do we calculate its value?

![adding R2 back in][tr_2_in-progress]

R2 is for when S1 is open. With no current flowing into R1, R2's job is to pull the base to the same voltage level as the emitter, ensuring the transistor shuts down. This is also useful to protect from stray electromagnetic interference (like from radio waves) that might induce a small amount of current in the base line.

So what's a good value for R2?

### step 4 (optional) - multiply R1 by ten to get R2
Where did this ten come from? It's just kind of a rule of thumb. It's a large enough multiple that R2 isn't going to mess horribly with the amount of current flowing into the base when S1 is closed (we've created a Kirchhoff junction), but still small enough to do something when S1 is open. Depending on what R1 is, you can take R2 down to as little as 5*R1. Going higher than 20*R1 is usually overkill.

#### circuit tr 2

[example breadboard][tr_2_bb]

![circuit tr 2][tr_2_schem]

If messing with your base current like this worries you, it's ok! Just run through the math. The voltage across R2 is going to be the same as v_BE (it's a voltage loop). If we assume the transistor is still saturated, that means v_BE = 0.75V. 0.75V / 100kΩ = 7.5µA. With the current junction, i_BE now equals i_R1 - i_R2. i_R1 equal v_R1 / R1, and v_R1 is still 5V - 0.75V = 4.25V.

i_BE = 4.25V/10kΩ - 7.5µA = 425µA - 7.5µA = 418 µA.

i_CE(max) = 418µA \* h_FE = 418µA \* 100 = **42mA**

So, we've still got more than enough available collector current, and our transistor works a little bit faster and more reliably. If you've got the room for it, I always recommend adding that second resistor.

## PNP BJTs
Working on it.


[trans-eq]: equations/npn-bjt-control.png "transistors work like this"
[bjt-pinout]: images/bjt-pinout.png "pins everywhere!"
[npn-bjt_sym]: images/npn-bjt_sym_wikipedia.png "NPN BJT symbol from Wikipedia"
[npn-bjt_volts]: images/npn-bjt_volts.png "NPN BJT symbol with junctions"
[high-low]: images/high-low-sw.png "high means voltage, low means ground"
[npn-low]: images/npn-low.png "NPNs are low side switches"
[tr_1_in-progress]: images/tr_1_schem_in-progress.png "still need to calculate resistor values"
[tr_2_in-progress]: images/tr_2_schem_in-progress.png "still need to calculate resistor values"
[tr_1_sans-r2]: images/tr_1_schem_sans-r2.png "R2!!!"
[tr_1_bb]: breadboard/tr_1_bb.png
[tr_1_schem]: tr_1_schem.png "transistor biased"
[tr_2_bb]: breadboard/tr_2_bb.png
[tr_2_schem]: tr_2_schem.png "better transistor biased"
