#include "../inc/header.h"

void destroy() { gtk_main_quit(); }

void SIGN_BOXES() {

    SignLog = GTK_CONTAINER(gtk_builder_get_object(builder, "SignLog"));
    SignBox = GTK_CONTAINER(gtk_builder_get_object(builder, "SignBox"));

    login = GTK_WIDGET(gtk_builder_get_object(builder, "Login"));
    password = GTK_WIDGET(gtk_builder_get_object(builder, "Password"));
    repeat = GTK_WIDGET(gtk_builder_get_object(builder, "Repeat"));
    hint = GTK_WIDGET(gtk_builder_get_object(builder, "Hint"));

    To_Sign = GTK_WIDGET(gtk_builder_get_object(builder, "To_sign"));
    Log_in = GTK_WIDGET(gtk_builder_get_object(builder, "Log_in"));

    To_Log = GTK_WIDGET(gtk_builder_get_object(builder, "To_log"));
    Sign_up = GTK_WIDGET(gtk_builder_get_object(builder, "Sign_up"));
}

void MAIN_BOXES() {
    
    Main = GTK_CONTAINER(gtk_builder_get_object(builder, "Main"));

    friends = GTK_CONTAINER(gtk_builder_get_object(builder, "friends"));
    Open_settings = GTK_WIDGET(gtk_builder_get_object(builder, "Open_settings"));
    Search_Friends = GTK_WIDGET(gtk_builder_get_object(builder, "Search_friends"));
    fbox = GTK_WIDGET(gtk_builder_get_object(builder, "fbox"));

    settings = GTK_CONTAINER(gtk_builder_get_object(builder, "settings"));
    Open_Friends = GTK_WIDGET(gtk_builder_get_object(builder, "Open_friends"));
    Change_password = GTK_WIDGET(gtk_builder_get_object(builder, "Change_password"));
    Log_out = GTK_WIDGET(gtk_builder_get_object(builder, "Log_out"));
    Theme = GTK_WIDGET(gtk_builder_get_object(builder, "Theme"));


    your_chat = GTK_CONTAINER(gtk_builder_get_object(builder, "your_chat"));

    your_friend = GTK_WIDGET(gtk_builder_get_object(builder, "your_friend"));
    friend_status = GTK_WIDGET(gtk_builder_get_object(builder, "friend_status"));

    Scroll = GTK_WIDGET(gtk_builder_get_object(builder, "Scroll"));
    cbox = GTK_WIDGET(gtk_builder_get_object(builder, "cbox"));

    Message_Box = GTK_WIDGET(gtk_builder_get_object(builder, "Message_Box"));
    Select_file_button = GTK_WIDGET(gtk_builder_get_object(builder, "Select_file_button"));
    Send_button = GTK_WIDGET(gtk_builder_get_object(builder, "Send_button"));
    

    chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(cbox), chat_box);
}

void NO_CONNECTION_BOX() {

    Connection_lost = GTK_CONTAINER(gtk_builder_get_object(builder, "connection-lost"));
    Reconnect_button = GTK_WIDGET(gtk_builder_get_object(builder, "Reconnect_button"));
}

void no_connection() {
    
  gtk_widget_show ( GTK_WIDGET(Connection_lost) );
  gtk_widget_hide ( GTK_WIDGET(Main) );
  gtk_widget_hide ( GTK_WIDGET(SignLog) );
}


void to_sign_up() {

    gtk_widget_hide (To_Sign);
    gtk_widget_hide (Log_in); 
    gtk_widget_hide (hint);

    gtk_widget_show (repeat);
    gtk_widget_show (To_Log);
    gtk_widget_show (Sign_up);
    
    STATE = 1;
}

void to_log_in() {

    gtk_widget_hide (repeat);
    gtk_widget_hide (To_Log);
    gtk_widget_hide (Sign_up);
    gtk_widget_hide (hint);

    gtk_widget_show (To_Sign);
    gtk_widget_show (Log_in);
    STATE = 0;
}

void open_settings() {

    gtk_widget_hide ( GTK_WIDGET(friends) );
    gtk_widget_show ( GTK_WIDGET(settings) );     
}

void open_friends() {

    gtk_widget_hide ( GTK_WIDGET(settings) );
    gtk_widget_show ( GTK_WIDGET(friends) );  
}

void log_out() {

    STATE = 0;
    gtk_widget_show ( GTK_WIDGET(SignLog) );
    gtk_widget_hide ( GTK_WIDGET(Main) );
    
    prepare();  
    struct info req;

    strcpy(req.action, "log_out");
    
    req.id = cl_info.id;
    strcpy(req.login, "");
    strcpy(req.password, "");  
    strcpy(req.key, cl_info.key);

    req.chat_id = -1; 
    req.friend_id = -1;
    strcpy(req.message, "");
    req.message_id = -1;
    req.time = -1; 
    gtk_container_remove(GTK_CONTAINER(cbox), chat_box);
    //gtk_container_remove(GTK_CONTAINER(cbox), chat_box2);
    gtk_container_remove(GTK_CONTAINER(fbox), friend_box);
    char *buf = stringify(&req);
    send_to_server(buf); 
}

void theme () {

    pthread_t conf1, conf2;
    if (gtk_switch_get_state ( GTK_SWITCH (Theme) ) == true) {

        gtk_switch_set_state (GTK_SWITCH(Theme), false);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(style), GTK_STYLE_PROVIDER_PRIORITY_USER);
        Config.theme = 0;
        Config.notifications = 0;
        pthread_create(&conf1, NULL, pre_update_config, NULL);
    }
    else {
        gtk_switch_set_state (GTK_SWITCH(Theme), true);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(style_dark), GTK_STYLE_PROVIDER_PRIORITY_USER);
        Config.theme = 1;
        Config.notifications = 0;
        pthread_create(&conf2, NULL, pre_update_config, NULL);
    } 
}

void *pre_update_config() {

    if (!update_config(&Config, CONFIG_PATH)) {
            printf("Cant save config \n");
    }
    else {
        printf("Config is saved \n");
    }
    pthread_exit(NULL);  
}

void open_main() {

    gtk_widget_hide ( GTK_WIDGET(Connection_lost) );
    gtk_widget_hide ( GTK_WIDGET(SignLog) );
    gtk_widget_hide ( GTK_WIDGET(settings) );  
    gtk_widget_show ( GTK_WIDGET(friends) );  
    gtk_widget_show ( GTK_WIDGET(Main) );   
}


// adding new contact
void create_chat(int chat_id, char *login)
{  
    GtkWidget *name_label; 
    GtkWidget *contact_button;
        GtkWidget *contact_box;
            GtkWidget *contact_name_box;
            GtkWidget *img_box;

    contact_button = gtk_button_new();
    gtk_widget_set_size_request(contact_button, 240, 50);
    
    contact_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(contact_button), contact_box);

    img_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(contact_box), img_box);


    contact_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(contact_box), contact_name_box);

    if (strcmp(login, cl_info.login) != 0)
        name_label = gtk_label_new(login);
    else
        name_label = gtk_label_new("Saved messages");

    gtk_box_pack_start(GTK_BOX(contact_name_box), name_label, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(friend_box), contact_button);
    
    gtk_widget_set_name (contact_button, "contact_button");
    gtk_widget_set_focus_on_click (contact_button, TRUE);

    gpointer *ptr = GINT_TO_POINTER(chat_id);

    g_signal_connect(G_OBJECT(contact_button), "clicked",
        G_CALLBACK(open_chat), ptr);

    gtk_widget_show_all(friend_box);
}

void create_message(int id, char *message, char* time)
{  
       
    GtkWidget *message_button = gtk_button_new();
    
    gtk_widget_set_margin_top(GTK_WIDGET(message_button), 5);
    gtk_widget_set_margin_start(GTK_WIDGET(message_button), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(message_button), 10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(message_button), 5);
    
    if (id == cl_info.id) {
        gtk_widget_set_halign(GTK_WIDGET(message_button), GTK_ALIGN_END);
    }
    else {
        gtk_widget_set_halign(GTK_WIDGET(message_button), GTK_ALIGN_START);
    }

    GtkWidget *message_time_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(message_button), message_time_box);

        GtkWidget *message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(message_time_box), message_box);
        gtk_widget_set_margin_end(GTK_WIDGET(message_box), 10);
        

        GtkWidget *time_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(message_time_box), time_box);

    GtkWidget *message_label = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(message_label), message);
    // gtk_label_set_line_wrap (message_label, false);
    // gtk_label_set_ellipsize (message_label, PANGO_ELLIPSIZE_START);
    // gtk_label_set_lines(GTK_LABEL(message_label), 5);
    // gtk_label_set_justify(GTK_LABEL(message_label), GTK_JUSTIFY_FILL );

    gtk_label_set_selectable (GTK_LABEL(message_label), TRUE);
    gtk_box_pack_start(GTK_BOX(message_box), message_label, FALSE, FALSE, 0);
    gtk_widget_set_name (message_button, "message");
    
   
   
    
    GtkWidget *time_label = gtk_label_new(time);
    gtk_label_set_selectable (GTK_LABEL(time_label), TRUE);
    gtk_box_pack_end(GTK_BOX(time_box), time_label, FALSE, FALSE, 0);
    gtk_widget_set_name (time_label, "time");

    gtk_box_pack_start(GTK_BOX(chat_box), message_button, FALSE, FALSE, 0);
    gtk_widget_show_all(cbox);

        
    
    gtk_widget_set_focus_on_click (message_button, TRUE);
    // g_signal_connect(G_OBJECT(contact_button), "clicked",
    //     G_CALLBACK(open_chat), NULL);

    scrolling();
}


void scrolling()
{
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(Scroll));
    gtk_adjustment_set_page_size (adj, 0);
    double value = gtk_adjustment_get_upper(adj);
    gtk_adjustment_set_value(adj, value);
}


/*void open_file( char *mass) {
    write(2, mass, strlen(mass));
}
void attach_file() {

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File",
                                        window,
                                        action,
                                        ("Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ("Open"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_file (chooser);
        open_file (filename);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}
*/
