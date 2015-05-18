# iPhone-Arduino-Ble-DSLR-Shutter-Trigger
Control your DSLR Camera with iPhone via Bluetooth Low Energy

Please check http://gokhan.in/blog/ble-shutter-trigger-for-iphone-and-arduino/ for schematics and fritzing designs.

DSLR Shutter Trigger Ble is an application iPhone and iPad. It’s connecting to Arduino via Bluetooth Low Energy Module (Currently tested with HM-10 BLE Module)

You can use your Arduino and DLSR Shutter Trigger Ble for shooting high speed photos such as popping water balloons, water drops / splashes.

DSLR Shutter Trigger Ble has 3 main trigger functions;

1) Sound Trigger Mode

You can shoot popping balloons, popping corns etc. with sound trigger events. Simply set a sensitivity level for sound input, select a fire option (camera or flash) then press the start button wait for a sound event. Also you can set a delay (in milliseconds) for triggering shutter.

When you select “Fire Flash” camera will goes to bulb mode. You can change Sample Arduino sketch for this option.

2) Laser Trigger Mode

You can shoot water drops / splashes with this mode. Laser beam hits the phototransistor and when a water drop blocks the laser beam going to phototransistor, function triggers the shutter.

You can set sensitivity level and delay and also you can select a fire method (flash or camera)

3) Standart Triggering Modes

This mode includes basic triggering modes.

Press to Shot : Each button click takes a shot

Self Timer : You can set a delay for shutter up to 30 seconds.

Bulb Mode : Press to button to activate bulb mode. Press again to stop.
