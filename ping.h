
void ping_command() {
	char *arg;
	Serial.print("P");
	arg = sCmd.next();
	if (arg != NULL) {
		Serial.write(' ');
		Serial.print(arg);
	}
	Serial.write('\n');
}
