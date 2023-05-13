# Kandidatnr: 10005
# Robot Palletizer Tycoon & Chris Annin Robot Arm Visualization

This repository houses two distinct yet interconnected components:

1. **Robot Palletizer Tycoon**: A real-time strategy game centered around managing a factory of robot arms.
2. **Chris Annin Robot Arm Visualization**: A real-time visualization tool for Chris Annin Robot Arms.

![Screenshot of the game](resources/images/game.png)

## Robot Palletizer Tycoon

Immerse yourself into the role of a factory manager in Robot Palletizer Tycoon. Your responsibility is to ensure a seamless process of picking up products from a conveyor belt with robot arms and stacking the boxes on pallets.

### Game Features

- **Factory Expansion**: Start with an empty warehouse and transform it into a bustling factory.
- **Upgrades**: Increase your efficiency by upgrading your robot arms, conveyor belts, and box spawn rates.
- **Rewards**: Earn money rewards every time a pallet is fully stacked.

![photo: A robot working in the factory](resources/images/game2.png)

## Chris Annin Robot Arm Visualization

This project also includes a standalone visualization tool for Chris Annin Robot Arms. Connect to the robot via serial USB and visualize the robot's movement in real-time.

### Visualization Features

- **Real-Time Visualization**: Connect to the robot via serial USB to see the robot movements in real-time.
- **Live Control**: Send data to the robot and control its movement in real-time.

![photo: Chris Annin Robot Arm Visualization](resources/images/controller.png)
![photo: Chris Annin Robot Arm Visualization](resources/images/visualize.png)

## Getting Started

### Requirements
- CLion
- vcpkg
- Real robot must be run using https://github.com/Plingaas/RobotArm.
- Windows for robot control (optional)
- Serial USB connection for robot control (optional)

Start by downloading CLion if you dont already have it installed. Once CLion is installed
create a new project from version control and copy the link found under the dropdown menu "<> Code".
Before you run the project you have to add a CMake option.

#### Adding CMake option on Windows:
1. Press file -> Settings -> Build Executement and Deployment -> CMake
2. Paste this under CMake options: -DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/scripts/buildsystems/vcpkg.cmake
3. Replace "<path to vcpkg" with your full path to your vcpkg folder.

#### Adding CMake option on MacOS:
1. Press CLion -> Preferences -> Build Executement and Deployment -> CMake
2. Paste this under CMake options: -DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/scripts/buildsystems/vcpkg.cmake
3. Replace "<path to vcpkg" with your full path to your vcpkg folder.

