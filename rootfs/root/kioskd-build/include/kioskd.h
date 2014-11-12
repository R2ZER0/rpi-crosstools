typedef struct kioskd Kioskd;

Kioskd* InitKioskd(int server_port, double render_inteval);
void RunKioskd(Kioskd* kioskd);
void DestroyKioskd(Kioskd* kioskd);