Lidar Distance and Mapping

Python or C++?

Define MVP

Basic distance mapping and hardcode.

Move Lidar to create a full range view.

Use ultrasonic sensors.

General scan mode (along/across). Focus and Detection mode. Width measurement mode (constant hand movement speed) 

Give a list and a count.

Use two sensors and compare result.

Use mm not cm.

Allowed flat wall detect difference +- 10mm
Fake Code, Different Detect Mode:

1st: Scanner Move left / right across the crack, then left -> middle -> right has detection spike for move left, move right opposite.

2nd: Depth Mode, L and R for wall, M for crack, crack depth = M - average(L + R)

3rd: Width Mode, ?
