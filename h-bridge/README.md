# intro to circuits - the h-bridge
The circuit that looks like an 'h'

## why use an h-bridge?
If we have a motor, we often want to be able to make that motor go either forwards or backwards. A motor will turn one way if current is flowing through it in one direction, and it will turn the other way if current is flowing in the other direction.

**An h-bridge allows us to send current in either direction through a motor to change its rotational direction.**

## what does an h-bridge look like?
An h-bridge is a series of four switches arranged around a motor like so:

![h-bridge](images/hbridge_wikipedia.png "an h-bridge")

Source: Cyril Buttay, CC-BY-SA 2.5,  http://en.wikipedia.org/wiki/File:H_bridge.svg

By alternation which switches are open and which are closed, the motor will turn clockwise or counterclockwise.

![h-bridge states](images/hbridge-states_wikipedia.png "turning the motor")

Source: Cyril Buttay, CC-BY-SA 2.5,  http://en.wikipedia.org/wiki/File:H_bridge_operating.svg

<figure>
<img src="images/hbridge-states_wikipedia.png" alt="h-bridge states">
<figcaption>Source: Cyril Buttay, CC-BY-SA 2.5,  http://en.wikipedia.org/wiki/File:H_bridge_operating.svg</figcaption>
</figure>


## building an h-bridge

### step 1 - control a motor with a PNP transistor

### step 2 - add an NPN transistor at the low side

### step 3 - re
