# intro to circuits - transistors (the fun stuff)
Transitioning into puns that are even worse than before.

## what is a transistor?
Transistors are the backbone of our digital world. There are millions of them in the computer you're on right now. I've given you twenty. They look a lot like this:

![transistor](images/transistors.jpg)

A transistor is like a valve controlling water flow, except it controls current flow. It can be closed, partially open, or fully open.

## types of transistors
The transistors that you have are called bi-polar junction transistors, or BJTs. They are so-called because they rely on a sandwich of two types of semiconductors. If you care about any of this, I highly recommend [the wikipedia page](http://en.wikipedia.org/wiki/Bipolar_junction_transistor).

The semiconductors are referred to as N-type and P-type. Because the BJT is a sandwich of these two materials, there are two possible configurations: NPN and PNP. We will start off with NPN BJTs.

Another important type of transistor is the FET (field-effect transistor). We will not use them in this course, but please know that they do exist, and operate differently than BJTs.

## NPN BJTs
You have five NPN transistors with the model number **2N3904**. You can see this written in very small letters on the flat face of the transistor. Every transistor with the same model number has the same specifications, and you can use the model number to find those specs.

![npn transistor](images/npn-transistor.jpg)

The symbol for an NPN transistor is this:

![npn byt symbol][npn-bjt_sym]

The E, B, and C stand for Emitter, Base, and Collector, respectively. Where do those names come from? Who cares? I forget. Probably something about holes and electrons. [You might be able to find out here](http://en.wikipedia.org/wiki/Bipolar_junction_transistor). Regardless of all that, **take note of the arrow on the emitter pin and the direction (outwards) that it's pointing.**

Do you remember that time I told you that transistors are like valves? It's still true. The current that an NPN transistor valve controls is the **current flowing between the collector and the emitter.**

What determines how "open" the "valve" is? The current flowing into the base. More specifically:

![NPN BJT equation](equations/npn-bjt-control.png)

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

The transistor's operation is governed by the equation: ![NPN BJT equation](equations/npn-bjt-control.png), so knowing that the CE junction is in series with our LED, the LED current is 20mA, and the gain of our transistor is 100, we can start building our circuit.

Applying the transistor equation gives us **i_BE = 0.2mA** (20mA / 100). This means that for our valve to be open enough to light our LED with the current we want (20mA), we need to ensure that 0.2mA flows through the base-emitter junction.

### the junctions
It's important to note that a BJT is effectively a diode sandwich. And diodes tend to drop about the same voltage no matter the current. In a BJT, there are two voltage drops we care about: the CE junction voltage drop, and the BE junction voltage drop. They are abbreviated v_CE, and v_BE.

![npn bjt voltage drops][npn-bjt_volts]

In red is v_BE, and in green is v_CE. Looking back at the data sheet, you'll notice that under the gain, it gives you some values for v_BE and v_CE (ignore the "SAT" for now). Notice that v_CE is much smaller than v_BE.

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

## biasing a transistor
Because BJTs operate by amplifying the base current by the gain, we need a way of regulating the base current. As we always do when trying to control current, we will use resistors to accomplish the task. The selection of proper resistor values for the circuit is called "transistor biasing".




[bjt-pinout]: images/bjt-pinout.png "pins everywhere!"
[npn-bjt_sym]: images/npn-bjt_sym_wikipedia.png "NPN BJT symbol from Wikipedia"
[npn-bjt_volts]: images/npn-bjt_volts.png "NPN BJT symbol with junctions"
[high-low]: images/high-low-sw.png "high means voltage, low means ground"
[npn-low]: images/npn-low.png "NPNs are low side switches"
