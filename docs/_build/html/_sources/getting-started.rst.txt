================================================================================
Getting Started
================================================================================

.. contents::
   :depth: 1
   :local:

Hardware Requirements
--------------------------------------------------------------------------------
**To start using X Controller, you need**

* One `brushles motor <https://en.wikipedia.org/wiki/Brushless_DC_electric_motor>`__.
* One encoder. We provide (and reccomend) an AMT 102-V encoder with your X1.
* A 6V-48V DC input power supply or a battery. 

Connections and Pinout
--------------------------------------------------------------------------------
* Solder the brushless motor power leads to the U,V, and W terminals on the X1.
* Solder your power supply or battery to the positive and negative terminals on the X1.
* Connect the encoder to the corresponding encoder pins. Use the included wiring harness if using the included encoder.

.. _install-xctrl:

Installing :code:`xctrl`
--------------------------------------------------------------------------------

.. tabs::
    .. tab:: macOS

        We are going to run the following commands for installation in Terminal.

        #. If you don't already have it, install homebrew: 

            .. code-block:: Bash

                /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"


        #. Install python:

            .. code-block:: Bash

                brew install python

        #. Install libusb:

            libusb is required for xctrl to communicate with X1 controller:
        
            .. code-block:: Bash

                brew install libusb

            .. _installxctrl:

        #. Install xctrl:

            Now that you have Python 3 and all the package managers, run:
        
            .. code-block:: Bash

                pip3 install --upgrade xctrl


    .. tab:: Linux

        #. `Install Python 3 <https://www.python.org/downloads/>`__. 
        
            For example, on Ubuntu, run

            .. code-block:: Bash

                sudo apt install python3 python3-pip


        #. Install xctrl by opening a terminal and typing

            .. code-block:: Bash

                sudo pip3 install --upgrade xctrl

Connecting to X1
--------------------------------------------------------------------------------
Each X1 controller comes with a unique name, written in white on the bottom corner of your X1.

After importing the xctrl library in your code, in order to connect to your X1, call :code:`xctrl.scan()`. This will automatically detect and 
ping all X1's connected to your computer over USB. :code:`scan()` automatically creates a Python XCtrl object
for every connceted X1 controller. For instance, :code:`xctrl0 = xctrl.scan()[0]` would assign to :code:`xctrl0` the XCtrl object correponding to the first X1 Controller connect to your device. 


(optional) Setting Limits 
--------------------------------------------------------------------------------
This part is optional. By default, your X1 controller is set to conservative limits
of 1A current limit and 1 turn/sec velocity limit. These serve to protect you and 
your setup during inital configuration. During operation, you will need to modify
these limits to suit your use case.

* To modify the limits, you can use :code:`xctrl0.set_limit(limit_name, limit_value)`. The available options you can use as :code:`limit_name` are :code:`"current"`, :code:`"velocity"`, :code:`"undervoltage"` and :code:`"overvoltage"`.



Motor and Encoder Configuration
--------------------------------------------------------------------------------
By default, your X1 controllor is (arbitaraily) configured for an Aerodrive SK3 270 KV motor with an AMT 102-V encoder set to 8192 ppr (provided with your X1 controller)

Motor and Encoder configuration involves three variables:

*  :code:`motor_torque_constant # torque constant meausred in Nm / A`
*  :code:`motor_pole_pairs # number of meagnetic pole pairs on your motor`
*  :code:`encoder_ppr # pulses per revolution of your encoder`

Torque constant configuration is optional. Motor pole pair configuration is necessary. Encoder PPR comes pre configured so long as you use the included AMT 102-V encoder

To configure any of the above values, use the following functions:

*  :code:`xctrl0.set_torque_constant(motor_torque_constant)`
*  :code:`xctrl0.set_poles(motor_num_pole_pairs)`
*  :code:`xctrl0.set_encoder_ppr(encoder_ppr)`
``
Calibration
--------------------------------------------------------------------------------
For your convenience, the calibration process is consolidated into a single step. All 
you need to do is to call the :code:`xctrl0.calibrate()` function and wait for the calibration to
be done. During calibration, your X1 controller measures encoder and motor properties such as
encoder offset, index position, motor phase resistance and inductance.

* Note: It is dangerous to operate X1 without calibration, however your X1 controller will not stop you
* Calibration is not required on startup so that you only need to calibrate one time (when you install a new motor)
* Do not switch motors or encoder mounting without recalibrating

Operation
--------------------------------------------------------------------------------
Now your are ready to operate your motor with your X1 controller! 
Controlling motors with your X1 involves 2 steps: setting the control mode and inputting a value.

* Pick a control mode with :code:`xctrl0.set_mode(mode)`, where mode can be one of :code:`"position"`, :code:`"velocity"` or :code:`"torque"`.
* Input a control value, use one of :code:`xctrl0.set_position(mode)`, :code:`xctrl0.set_velocity(mode)` or :code:`xctrl0.set_position(mode)`, depending on which of the control mode the X1 controller is set to. 
* For position control, the default unit used by X1 controller is radians. Noted that if you want the position to match the radians input, you might need to go back and correctly configure the controller with the specific motor specifications.
* For velocity control, the default unit used by X1 controller is radians/second. Similar to position control, configuring the controller is only needed if you want the velocity of the motor to be exact.
* For torque control, the default unit used by X1 controller is Nm (Newton-metre). Similar to above, configuring the controller is only needed if you want the torque of the motor to be exact.
* Sending more than 100 commands per second is not reccomended
