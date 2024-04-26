#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NEW_GTK_TOPLEVEL "new"
#define DESTROY_OLD_TOPLEVEL "destroy"
#define max 100


GtkWidget *window;
GtkWidget* username_entry;
GtkWidget* rec_code_entry;
GtkWidget* forgot_btn;
GtkWidget* forgot_check;
bool flag = false;
char authenticationOTP[20];
FILE* __db__;
FILE* gmailExecutable;



void __init__(char* smtpServer, char* appPassword, char* subject, char* content, char* receiver){
  gmailExecutable = fopen("sendMail.py","w");
  fprintf(gmailExecutable, "import smtplib\n");
  fprintf(gmailExecutable, "senderMail = \"%s\"\n", smtpServer); 
  fprintf(gmailExecutable, "appPassword = \"%s\"\n", appPassword); 
  fprintf(gmailExecutable, "gmailSubject = \"%s\"\n", subject); 
  fprintf(gmailExecutable, "gmailContent = \"%s\"\n", content); 
  fprintf(gmailExecutable, "gmailReceiver = \"%s\"\n", receiver); 
  fprintf(gmailExecutable, "gmail = gmailReceiver.split()\n"); 
  fprintf(gmailExecutable, "server = smtplib.SMTP('smtp.gmail.com', 587)\n"); 
  fprintf(gmailExecutable, "server.starttls()\n"); 
  fprintf(gmailExecutable, "server.login(senderMail, appPassword)\n"); 
  fprintf(gmailExecutable, "message = f'''Subject: {gmailSubject}\n\n{gmailContent}'''\n"); 
  fprintf(gmailExecutable, "server.sendmail(senderMail, gmail, message)\n"); 
  fclose(gmailExecutable);
}

int sendMail(int returnVal){
  system("python3 sendMail.py");
  switch(returnVal){
  case 0: return 0; break;
  case -1: return -1; break;  
  default: return 0; break;
  }
}

void otpFunction(char* email, char* otp_to_receive){
  time_t current_time;
  struct tm *time_info;

  current_time = time(NULL);

  time_info = localtime(&current_time);

  int hour = time_info->tm_hour;
  int minute = time_info->tm_min;
  int second = time_info->tm_sec;
  char otp[10];
  sprintf(otp, "%d%d%d%d", (int)(hour/10), (int)(hour%10) + (int)(minute/10), (int)(minute%10) + (int)(second/10), (int)(second%10));
  sprintf(otp_to_receive, "%s", otp);
  char _otp[100];
  sprintf(_otp, "OTP is %s", otp_to_receive);
  __init__("avian.aura.ics@gmail.com", "zrki ycwq setx uyrp", "OTP for login", _otp, email);
  sendMail(0);
}

bool checkOTP(const char* user, char* actual){
  return (strcmp(user, actual) == 0) ? true : false;
}


bool forgotPasswordcheck(GtkWidget* widget, GdkEvent* event){
    const char* uname =  gtk_entry_get_text(GTK_ENTRY(username_entry));

    __db__ = fopen("db.csv", "r");
    char row[max];
    char* token;
    fgets(row, max, __db__);
    while(fgets(row, max, __db__)){
        token = strtok(row, ","); // 1 
        if(strcmp(token,uname) == 0){
            token = strtok(NULL, ", "); // 2
            token = strtok(NULL, ", "); // 3
            token = strtok(NULL, ", "); // 4
            token = strtok(NULL, ", "); // 5
            token[strcspn(token, "\n")] = '\0';
            otpFunction(token, authenticationOTP);
            fclose(__db__);
            return true;
        }
    }
    fclose(__db__);
    return false;
}

void forgot_but_login(GtkWidget* widget, GdkEvent* event){
    const char* rc =  gtk_entry_get_text(GTK_ENTRY(rec_code_entry));
    if(checkOTP(rc, authenticationOTP)){
        flag = true;
    }
}

bool forgot_password_init(int argc, char* argv[], char* _name){
    char* args[] = {NEW_GTK_TOPLEVEL, DESTROY_OLD_TOPLEVEL};
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Avian Aura : Login");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 3. Username
    GtkWidget *hbox_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_3);
    gtk_widget_set_margin_start(hbox_3, 20);
    gtk_widget_set_margin_end(hbox_3, 20);
    gtk_widget_set_margin_top(hbox_3, 20);

    GtkWidget *username_label = gtk_label_new("Username: ");
    gtk_box_pack_start(GTK_BOX(hbox_3), username_label, FALSE, FALSE, 0);
    username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_3), username_entry, FALSE, FALSE, 0);

    // 5. Recovery code
    GtkWidget *hbox_5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_5);
    gtk_widget_set_margin_start(hbox_5, 20);
    gtk_widget_set_margin_end(hbox_5, 20);
    gtk_widget_set_margin_top(hbox_5, 20);

    GtkWidget *recovery_code = gtk_label_new("OTP: ");
    gtk_box_pack_start(GTK_BOX(hbox_5), recovery_code, FALSE, FALSE, 0);
    rec_code_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_5), rec_code_entry, FALSE, FALSE, 0);

    // 6. Button
    forgot_btn = gtk_button_new_with_label("Login");
    g_signal_connect(forgot_btn, "clicked", G_CALLBACK(forgot_but_login), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), forgot_btn, FALSE, FALSE, 0);
    
    // 7. send OTP button
    forgot_check = gtk_button_new_with_label("Send OTP");
    g_signal_connect(forgot_check, "clicked", G_CALLBACK(forgotPasswordcheck), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), forgot_check, FALSE, FALSE, 0);

    // .showall()
    gtk_widget_show_all(window);

    // .mainloop()
    gtk_main();
    return flag;
}
