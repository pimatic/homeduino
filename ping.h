
void ping_command() {
	char *arg;
	Serial.print("PING");
	arg = sCmd.next();
	if (arg != NULL) {
		Serial.write(' ');
		Serial.print(arg);
	}
	Serial.print("\r\n");
}
