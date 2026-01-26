a (int i) {
	if (i>0)
		a(--i);
	else
		printf("i has reached zero");
	return;
}

main() {
a(1);
}
