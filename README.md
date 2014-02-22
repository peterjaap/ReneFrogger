Rene Frogger
============
This is my first attempt to program a game on an Arduino, using a 16x2 rows LCD. It's a simple Frogger type game with a horizontal orientation (get from left to right instead of from bottom to top).

![screen shot 2014-02-22 at 18 15 21 pm](https://f.cloud.github.com/assets/431360/2238264/2c2ecb50-9be5-11e3-99a3-a2530dec3659.png)
![screen shot 2014-02-22 at 18 15 31 pm](https://f.cloud.github.com/assets/431360/2238263/2c201f24-9be5-11e3-81b0-27d2f1ad7dce.png)
![screen shot 2014-02-22 at 18 15 39 pm](https://f.cloud.github.com/assets/431360/2238262/2c032bc6-9be5-11e3-8505-65f3f90ffb9f.png)
What do you need
----------------
An Arduino (I used an Uno but a Duemilanove should work too) and a 16x2 LCD with a key pad. I used the excellent [DFRobot LCD Keypad Shield][1] which you can get from [DealExtreme here][2] for about 7 dollars. You will also need to add the [SimpleTimer][3] plugin to your Arduino dir.

Click the shield on the Arduino, upload the sketch and you're good to go!
How to play
-----------
Up to go up, down to go down, left to go left and finally, not surprisingly, right to go, well, right.

Select the difficulty at the start (easy = 1 monster, medium = 2 monsters, hard = 3 monsters). You start at 100 points and there is one point deducted for every second that passes and for every key press that you need to get to the other side.

Tip; watch out for the monsters!!!111!1!1

  [1]: http://www.dfrobot.com/index.php?route=product/product&product_id=51
  [2]: http://dx.com/p/lcd-keypad-shield-for-arduino-duemilanove-lcd-1602-118059?Utm_rid=89236863&Utm_source=affiliate
  [3]: http://playground.arduino.cc/Code/SimpleTimer
