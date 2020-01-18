<h1 align="center">
	<img src="images/header_animation.gif" alt="WARM WOODY KNOCKER" />
</h1>

**WARM WOODY KNOCKER** is an Arduino based metronome that uses solenoids beating a wooden box to produce sound.

## Features

* Wide range of tempos.

* Linear rhytms. Meter and subdivision are both configurable, so anything between 1/4 and 16/16 is possible.

* Irregular patterns like Clave, Songo or Saiidi. Swing rhytms can be simulated in this mode as well. Patterns of arbitrary length and subdivision are supported. Two "tracks" (each controlling it's own actuator) with three sound levels each (off / regular / accented) are available while programming a pattern. (TODO: wiki page)

* Volume adjustment (TODO: wiki page). Level range is quite wide in theory, but not the whole range gives stable result, because of mechanics instability.

## Building the project

TODO

### Configuration

TODO

## Hardware part

### Supported hardware

Any Arduino-compatible board should work. Original version of WWK was build on Seeeduino v3.0 (clone of Duemilanove). Currently an Arduino Nano board is used for development of v2.

### Schematics

All values are given for reference and can be changed in a wide range without affecting functionality.

[![**v1** schematics](./images/schematics_v1_thumb.png)<br>**v1** schematics](./images/schematics_v1.png)

* U1 is optional and may be removed if your transformer gives no more than 12v. In that case, display power should be connected to Arduino 5V output. The original WWK build was intended to work all day long, that's why it is mains powered.

* Q1 and Q2 are any N-channel MOSFETs that can be driven by logic levels. The parts I've used seems to be an overkill, but that was what I had around without any use.

### Construction

Original WWK was built inside a wooden box, that used to be a mic case some day. Front panel with Arduino board attached and the transformer are fixed on one half of the box, and the power board with solenoids are on the another half. With power wire detached, the box can be locked with the original latch which makes it safe to carry the device.

Electromagnetic actuators (push type) are pointed to one of the box walls. Having two separate actuators makes possible to play accents or patterns. It's a tricky part of building the WWK to find appropriate spot on the wall to hit by actuators and adjust the gap between them. Even small shift may give big difference in sound. When adjusting the gap, you should also check different pulse widths (volume levels), as these parameters are interdependent. I've ended up with about 0.3 mm. I screwed small oak tips to the actuators and protected the box wall with one or two layers of electrical tape just on the hit point. Dents and cracks are quite possible, I have to admit after some experiments :), especialy if you set a large gap an wide pulses.

## Road map

* Better support for battery powered hardware

* Restoring last used settings

* Tap tempo / tempo synchronization

* Patterns recording

* Adjustable swing factor

* Better animations without compromising playback accuracy
