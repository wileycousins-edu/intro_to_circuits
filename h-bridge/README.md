# intro to circuits - the h-bridge
The circuit that looks like an 'h'

## why use an h-bridge?
If we have a motor, we often want to be able to make that motor go either forwards or backwards. A motor will turn one way if current is flowing through it in one direction, and it will turn the other way if current is flowing in the other direction.

**An h-bridge allows us to send current in either direction through a motor to change its rotational direction.**

## what does an h-bridge look like?
An h-bridge is a series of four switches arranged around a motor like so:

![h-bridge with switches][hbridge_wikipedia]

Source: Cyril Buttay, CC-BY-SA 2.5,  http://en.wikipedia.org/wiki/File:H_bridge.svg

By alternating which switches are open and which are closed, the motor will turn clockwise or counterclockwise.

![h-bridge states](images/hbridge-states_wikipedia.png "turning the motor")

Source: Cyril Buttay, CC-BY-SA 2.5,  http://en.wikipedia.org/wiki/File:H_bridge_operating.svg

We can build what's called a "truth table" to examine the different possible states of an h-bridge. In this truth table, a '1' represents a closed switch, a '0' represents and open switch, and an 'x' represents "doesn't matter".

| S1  | S2  | S3  | S4  | Result                  |
| --- | --- | --- | --- | ----------------------- |
| 0   | 0   | 0   | 0   | Motor coasts            |
| 1   | 1   | x   | x   | Shoot through (**bad**) |
| x   | x   | 1   | 1   | Shoot through (**bad**) |
| 1   | 0   | 1   | 0   | Motor brakes (fine)     |
| 0   | 1   | 0   | 1   | Motor brakes (fine)     |
| 1   | 0   | 0   | 1   | Clockwise               |
| 0   | 1   | 1   | 0   | Counterclockwise        |

First, let me draw your attention to the shoot through conditions. A shoot through means that the current is going to shoot straight from Vin to ground, missing the motor entirely, and probably damaging your circuit. Shoot through should be avoided.

Coasting and braking are what they sound like. If the motor is moving, and then all switches are opened, the motor will coast until friction stops it. Conversely, if the motor is moving, and a braking condition is applied, the motor will stop turning. This is because both terminals of the motor are held at the same voltage level, so no current can flow through it.

Finally, and most interestingly, there are the last two conditions in the table. These are the ones that make the motor turn. Look at the table and the circuit diagrams above it and see if they make sense.

## building an h-bridge
While we could build an h-bridge with our push-buttons, we will not. Why? Ideally, [our motor](https://www.sparkfun.com/products/11696) wants 100mA. Our switches are only rated at 50mA. So, instead of using just pushbuttons, we will use transistors to switch the motor loads, and pushbuttons to control the transistors.

### step 1 - control a motor with a PNP transistor
To start, we will use a single PNP transistor (2N3906) as a high-side switch to control a motor. This way, we can figure out what value resistors we need to bias our transistors to saturation. Don't remember what transistor biasing is all about? Try reviewing the [transistor material](../transistors).

Our load (as I mentioned a second ago) is 100 mA. Let's go to our [transistor's data sheet][2N3906] and look up its characteristics with a collector current of 100mA.

![2N3906 on characteristics](images/2n3906-on.png "no pain no gain")

From this table, with i_C = 100mA (the datasheet says -100mA because in a PNP transitor, current flows out of the collector), we see that the minimum gain is going to be 30. So **we will use h_FE = 30** in our calculations.

We also can see that as i_C gets higher, so does the saturation voltage drop from the emitter to the base. Looking at this table (and at the graph on the third page relating V_BE(sat) to i_C, **we will use V_BE,sat = 1.0V** in our calculations.

![transistor biasing](images/transistor-bias-1.png)

Using a gain of 30 and a load current of 100mA, we need a base current of 100mA/30 = 3.3mA. To ensure saturation, we will bump that up to **i_B = 5mA**.

Ignoring the existence of R2 for a moment, our base current is going to be equal to the current going through R1. To find the proper value of R1, we need to find the value of v1. v1 = 5V - v_BE(sat), so **v1 = 4.0V**. If we want i_1 to equal 5mA, and v_1 = 4.0V, using Ohm's law we find that **R1 needs to be less than or equal to 800Ω**. The closest resistor we have that is less than 800Ω is 330Ω, so let's use **R1 = 330Ω**.

Now, acknowledging that R2 exists (as a safety precaution; it pulls the transistor to off by default), let's use our biasing rule of thumb and select a value that is 10 times R1. So **R2 = 3.3kΩ**. Since the voltage drop across R2 is equal to v_BE,sat, we know that the i_R2 is going to equal 1.0V/3.3kΩ when the switch is down. This gives us **i_R2 = 0.3mA**. Knowing that i_R1 will be equal to i_B + i_R2 (Kirchhoff's Current Law), and **i_R1 = 4.0V/330Ω = 12.1mA**, we can back out that **i_B = i_R1-i_R2 = 11.8mA**. This is plenty of current to saturate the transistor.

Now, we're also going to **add a protection diode to the transistor** to protect the it from voltage spikes from sudden changes in supply current to the motor. For extra breadboard room, **we're also going to ditch R2** (even after all those calculations). It's a good idea to have R2, but it's not necessary, so we'll be fine. This gives us:

#### circuit hb 1
[example breadboard layout][hb_1_bb]

![circuit hb 1][hb_1_schem]

With this circuit, if we press the button, the motor should turn.

### step 2 - add an NPN transistor at the low side

Now, we will add an NPN transistor (2N3904) as a low side switch. The resulting circuit will be a "half h-bridge".

Since we are using matching PNP and NPN BJTs (2N3906 and 2N3904, respectively), we don't have to go through all the transistor math again; matching BJTs are designed to have matching properties. So the gain, saturated voltage drops, etc will have the same magnitude. So, using the same value resistor with a 2N3904 gives us:

#### circuit hb 2
[example breadboard layout][hb_2_bb]

![circuit hb 2][hb_2_schem]

With this circuit, the motor will only turn if we hold down both buttons.

Pay close attention to the direction of the protection diodes. They are alligned so that they are pointing in the opposite direction of current flow through the transistors. When the transistors are shut off (the switch is open), the diodes will allow excess current from the motor to flow back into the positive end of the power supply rather than letting it try to force its way through a diode.

### step 3 - copy / paste for a full h-bridge
Now we just have to duplicate our high and low side transistor switches to give us a full h-brige.

#### circuit hb 3
[example breadboard layout][hb_3_bb]

![circuit hb 3][hb_3_schem]

Compare this to the schematic from the beginning with just switches:

![h-bridge with switches][hbridge_wikipedia]

Looking back at our original truth table: pushing down S1 and S4 will make the motor turn one way, and pushing down S2 and S3 will make it turn the other way. **DO NOT PRESS S1 AND S2 AT THE SAME TIME. DO NOT PRESS S3 AND S4 AT THE SAME TIME**. This will cause a shoot through and possibly ruin your transistors.

## making the h-bridge easier
Having four switches to control an h-bridge isn't super convenient. Is there any way we could use just two switches?

Yes there is.

### add an NPN to the high side switches
With our current circuit, to make the motor move we need to activate a PNP and an NPN transistor. Unfortunately, to turn a PNP on, we need to pull the base lower than the emitter, while to turn an NPN on, we need to pull the base higher than the emitter. Current needs to flow out of the base for a PNP, and into the base for an NPN. If only we could use an NPN for those high side switches, we could tie the bases together and use one switch.

Unfortunately, NPNs do not function well as high-side switches. This leaves us wanting to control the high-side switch with an NPN for logic reasons, but needing the load switch to be a PNP for electrical reasons. What's the solution?

We can control the PNP with an NPN. Let's try adapting circuit hb 1:

#### circuit hb 1

![circuit hb 1][hb_1_schem]

When we push down S1, we allow current to flow into Q1's emitter and out of the base, activating the emitter to collector junction. We know from our previous calculations that i_R1 is going to be about 12mA. So let's replace S1 with a NPN transistor that will allow more than 12mA to flow to ground:

#### circuit hb 1 modified

[example breadboard layout][hb_1_bb]

You don't need to build this one; in fact, please avoid tearing up your existing h-bridge.

![modified circuit hb 1][hb_1_modified_schem]

Now, instead of connecting to ground, our switch connects to Vcc in order to activate the NPN. This, in turn, activates the PNP. Notice the 10kΩ resistor on the base of the NPN transistor. Is this going to work? Use the 2N3904 datasheet and see if you can solve for the currents.

Now, if we apply these modifications to our full h-bridge:

#### circuit hb final

[example breadboard layout][hb_final_bb]

![final h-bridge][hb_final_schem]

Now, pressing one button should turn the motor one way, and the other button should turn the motor the other way. **DO NOT PRESS BOTH BUTTONS AT ONCE**.

## h-bridges are done
Congratulations! You've built an h-bridge. If you ever find yourself needing an h-bridge in the future, I would highly recommend buying a dedicated h-bridge integrated circuit. But hey, now if you can't / don't want to do that, you also know how to build one with discreet components. Awesome.


[hbridge_wikipedia]: images/hbridge_wikipedia.png "h-bridge theory"
[2N3906]: https://www.fairchildsemi.com/ds/2N/2N3906.pdf "2N3906 datasheet"
[hb_1_bb]: breaboard/hb_1_bb.png
[hb_1_schem]: hb_1_schem.png
[hb_2_bb]: breadboard/hb_2_bb.png
[hb_2_schem]: hb_2_schem.png
[hb_3_bb]: breadboard/hb_3_bb.png
[hb_3_schem]: hb_3_schem.png
[hb_1_modified_bb]: breadboard/hb_1_modified_bb.png
[hb_1_modified_schem]: hb_1_modified_schem.png
[hb_final_bb]: breadboard/hb_final_bb.png
[hb_final_schem]: hb_final_schem.png
