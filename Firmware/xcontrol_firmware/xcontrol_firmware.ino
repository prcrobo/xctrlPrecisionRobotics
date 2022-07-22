float current_limit;
float velocity_limit;
float undervoltage_limit;
float overvoltage_limit;

float torque_constant;
int poles_num;
float encoder_ppr;
int mode; // 0 is position, 1 is velocity, 2 is torque

float target_position;
float target_velocity;
float target_torque;

String controller_name = "robot";

// input string prefix
int first_prefix_len = 3;
String set_prefix = "set";
String calibrate_prefix = "cal";
String control_input_prefix = "inp";


// prefix of set paramter function substring
int set_param_prefix_len = 4;
String set_limit_prefix = "limi";
String set_torque_constant_prefix = "torc";
String set_poles_num_prefix = "pole";
String set_encoder_ppr_prefix = "eppr";
String set_control_mode_prefix = "mode";

void setup() {
  Serial.begin(115200);
}
void loop() {
  parse_string_input();
//  Serial.print(controller_name);

}

void controller_ping() {
  Serial.println(controller_name);
}

void parse_string_input() {
  if (Serial.available()) {
    String string_input = Serial.readString();
    // first prefix can be one of "set", "cal" or "inp"
    String prefix = string_input.substring(0, first_prefix_len);
    String without_prefix = string_input.substring(first_prefix_len+1);
    if (prefix.equals(set_prefix)) {
      set_parameter(without_prefix);
    } else if (prefix.equals(calibrate_prefix)) {
      calibrate();
    } else if (prefix.equals(control_input_prefix)) {
      control_input_update(without_prefix);
    } else if (prefix.equals("pin")) {
      controller_ping();
    }
  }
}

void set_parameter(String input) {
  String prefix = input.substring(0, set_param_prefix_len);
  String without_prefix = input.substring(set_param_prefix_len+1);
  if (prefix.equals(set_limit_prefix)) {
    set_limit(without_prefix);
  } else if (prefix.equals(set_torque_constant_prefix)) {
    set_torque_constant(without_prefix);
  } else if (prefix.equals(set_poles_num_prefix)) {
    set_poles_num(without_prefix);
  } else if (prefix.equals(set_encoder_ppr_prefix)) {
    set_encoder_ppr(without_prefix);
  } else if (prefix.equals(set_control_mode_prefix)) {
    set_control_mode(without_prefix);
  } 
}

void control_input_update(String input_string) {
  String prefix = input_string.substring(0, 3);
  float input_value = input_string.substring(4).toFloat();

  if (prefix.equals("pos")) {
    target_position = input_value;
  } else if (prefix.equals("vel")) {
    target_velocity = input_value;
  } else if (prefix.equals("tor")) {
    target_torque = input_value;
  }
}


void calibrate() {
}

void set_limit(String input_string) {
  String limit_name = input_string.substring(0, 3);
  float limit_value = input_string.substring(4).toFloat();

  if (limit_name.equals("cur")) {
    current_limit = limit_value;
  } else if (limit_name.equals("vel")) {
    velocity_limit = limit_value;
  } else if (limit_name.equals("und")) {
    undervoltage_limit = limit_value;
  } else if (limit_name.equals("ove")) {
    overvoltage_limit = limit_value;
  } 
}

void set_torque_constant(String input) {
  torque_constant = input.toFloat();
}

void set_poles_num(String input) {
  poles_num = input.toInt();
}

void set_encoder_ppr(String input) {
  encoder_ppr = input.toFloat();
}

void set_control_mode(String input) {
  if (input.equals("pos")) {
    mode = 0;
  } else if (input.equals("vel")) {
    mode = 1;
  } else if (input.equals("tor")) {
    mode = 2;
  }
}
