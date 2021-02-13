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

    // sidebar
    sidebar_overlay = GTK_OVERLAY(gtk_builder_get_object(builder, "sidebar-overlay"));
    friends = GTK_CONTAINER(gtk_builder_get_object(builder, "friends"));
    Open_settings = GTK_WIDGET(gtk_builder_get_object(builder, "Open_settings"));
    Search_Friends = GTK_WIDGET(gtk_builder_get_object(builder, "Search_friends"));
        error_box1 = GTK_WIDGET(gtk_builder_get_object(builder, "error-box1"));
        error_message1 = GTK_WIDGET(gtk_builder_get_object(builder, "error-message1"));
    GtkWidget   *Contacts = GTK_WIDGET(gtk_builder_get_object(builder, "Contacts")); gtk_widget_set_name(Contacts, "Contacts");
    fbox = GTK_WIDGET(gtk_builder_get_object(builder, "fbox"));

    settings = GTK_CONTAINER(gtk_builder_get_object(builder, "settings"));
    Open_Friends = GTK_WIDGET(gtk_builder_get_object(builder, "Open_friends"));
    Change_password = GTK_WIDGET(gtk_builder_get_object(builder, "Change_password"));
        new_password = GTK_WIDGET(gtk_builder_get_object(builder, "new_password"));      
        error_box2 = GTK_WIDGET(gtk_builder_get_object(builder, "error-box2"));
        error_message2 = GTK_WIDGET(gtk_builder_get_object(builder, "error-message2"));
    Log_out = GTK_WIDGET(gtk_builder_get_object(builder, "Log_out"));

    Theme = GTK_WIDGET(gtk_builder_get_object(builder, "Theme"));
    Notifications = GTK_WIDGET(gtk_builder_get_object(builder, "Notifications"));
    Localization = GTK_WIDGET(gtk_builder_get_object(builder, "Localization"));


    // main chat block
    header_box = GTK_CONTAINER(gtk_builder_get_object(builder, "header-box"));
    your_chat = GTK_CONTAINER(gtk_builder_get_object(builder, "your_chat"));

    your_friend = GTK_WIDGET(gtk_builder_get_object(builder, "your_friend"));
    friend_status = GTK_WIDGET(gtk_builder_get_object(builder, "friend_status"));

    Scroll = GTK_WIDGET(gtk_builder_get_object(builder, "Scroll"));
    cbox = GTK_WIDGET(gtk_builder_get_object(builder, "cbox"));

    Message_Box = GTK_WIDGET(gtk_builder_get_object(builder, "Message_Box"));

    Edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_button")); 
    go_edit = GTK_WIDGET(gtk_builder_get_object(builder, "go-edit"));
    Delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "Delete_button")); 
    Send_button = GTK_WIDGET(gtk_builder_get_object(builder, "Send_button"));
        g_signal_connect(G_OBJECT(Send_button), "clicked", send_message, NULL);
        g_signal_connect(G_OBJECT(Send_button), "activate", send_message, NULL);
    go_to_chats = GTK_WIDGET(gtk_builder_get_object(builder, "go_to_chats"));

    // right side menu
    go_chats = GTK_CONTAINER(gtk_builder_get_object(builder, "go-chats"));

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
    
    gtk_label_set_text(GTK_LABEL(error_message1), "");
    gtk_entry_set_text(GTK_ENTRY(Search_Friends), "");
    if (gtk_widget_get_visible(error_box1) == true)
        gtk_widget_hide (error_box1);
    gtk_widget_hide ( GTK_WIDGET(friends) );
    gtk_widget_show ( GTK_WIDGET(settings) );     
}

void open_friends() {

    if (gtk_widget_get_visible(new_password) == true) {
        gtk_widget_hide(new_password);
    }
    if (gtk_widget_get_visible(error_box2) == true) {
        gtk_widget_hide(error_box2);
    }
    gtk_widget_hide ( GTK_WIDGET(settings) );
    gtk_widget_show ( GTK_WIDGET(friends) );  
}

void log_out() {

    if (gtk_widget_get_visible(new_password) == true) {
        gtk_widget_hide(new_password);
    }
    if (gtk_widget_get_visible(error_box2) == true) {
        gtk_widget_hide(new_password);
    }
    STATE = 0;
    gtk_widget_show ( GTK_WIDGET(SignLog) );
    gtk_widget_hide ( GTK_WIDGET(Main) );
    
    prepare();  
    if (!update_localdata(&cl_info, LD_PATH)) {
        printf("Can`t save localdata\n");
    }
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
        pthread_create(&conf1, NULL, pre_update_config, NULL);
    }
    else {
        gtk_switch_set_state (GTK_SWITCH(Theme), true);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(style_dark), GTK_STYLE_PROVIDER_PRIORITY_USER);
        Config.theme = 1;
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
        gtk_widget_set_size_request(img_box, 40, 50);
        gtk_container_add(GTK_CONTAINER(contact_box), img_box);

        contact_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(contact_box), contact_name_box);
        gtk_widget_set_name (contact_name_box, "contact_name_box");

    if (strcmp(login, cl_info.login) != 0) { 
        name_label = gtk_label_new(login);
        gtk_widget_set_name (img_box, "avatar");
    }
    else { 
        name_label = gtk_label_new("Saved messages");
        gtk_widget_set_name (img_box, "saved");
    }

    gtk_box_pack_start(GTK_BOX(contact_name_box), name_label, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(friend_box), contact_button);
    
    gtk_widget_set_name (contact_button, "contact_button");
    gtk_widget_set_focus_on_click (contact_button, TRUE);

    gpointer *ptr = GINT_TO_POINTER(chat_id);

    g_signal_connect(G_OBJECT(contact_button), "clicked",
        G_CALLBACK(open_chat), ptr);

    gtk_widget_show_all(friend_box);
}


void create_message(int id, char *message, int message_id, char* time)
{  
    GtkWidget *message_button = gtk_button_new();
    
    gtk_widget_set_margin_start(GTK_WIDGET(message_button), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(message_button), 10);
    
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
        

        GtkWidget *time_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(message_time_box), time_box);

    GtkWidget *message_label = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(message_label), message);
    gtk_label_set_selectable (GTK_LABEL(message_label), TRUE);
    gtk_label_set_max_width_chars (GTK_LABEL(message_label), 40);
    gtk_label_set_line_wrap (GTK_LABEL(message_label), TRUE);
    gtk_label_set_line_wrap_mode (GTK_LABEL(message_label) , PANGO_WRAP_WORD_CHAR);

    gtk_label_set_selectable (GTK_LABEL(message_label), TRUE);
    gtk_box_pack_start(GTK_BOX(message_box), message_label, FALSE, FALSE, 0);
    gtk_widget_set_name (message_button, "message");
    
   
   
    
    GtkWidget *time_label = gtk_label_new(time);
    gtk_label_set_selectable (GTK_LABEL(time_label), TRUE);
    gtk_box_pack_end(GTK_BOX(time_box), time_label, FALSE, FALSE, 0);
    gtk_widget_set_name (time_label, "time");

    gtk_box_pack_start(GTK_BOX(chat_box), message_button, FALSE, FALSE, 4);

    gtk_widget_set_sensitive(cbox, FALSE);
    // gtk_widget_set_focus_on_click (message_button, TRUE);

    edit_t *Edit = g_new(edit_t, 1);
    Edit->message_lab = message_label;
    Edit->message_id = message_id;
    strcpy(Edit->message, message);
    g_signal_connect(G_OBJECT(message_button), "clicked", editing, Edit);
     
    scrolling();
    gtk_widget_show_all(cbox);
    
}

void editing(GtkButton *button, edit_t *Edit) {

    GlobalEdit.message_lab = Edit->message_lab;
    GlobalEdit.butt = button;
    GlobalEdit.message_id = Edit->message_id;
    strcpy(GlobalEdit.message, Edit->message);
    gtk_entry_set_text(GTK_ENTRY(Message_Box), Edit->message);
}

void edit_delete() {

    if (gtk_widget_get_visible(GTK_WIDGET(header_box)) == true) {

        gtk_widget_hide(go_edit);
        gtk_widget_show(Edit_button);
        gtk_widget_set_sensitive(cbox, TRUE);
        gtk_widget_hide(GTK_WIDGET(header_box));
        gtk_widget_hide(GTK_WIDGET(sidebar_overlay));
        gtk_widget_show(Delete_button);
        gtk_widget_hide(Send_button);
        gtk_widget_show(GTK_WIDGET(go_chats));
        gtk_entry_set_placeholder_text(GTK_ENTRY(Message_Box), "Choose message to edit");
        g_signal_connect(G_OBJECT(Message_Box), "activate", edit_message, NULL);
    }
    else {
        gtk_widget_show(go_edit);
        gtk_widget_hide(Edit_button);
        gtk_widget_set_sensitive(cbox, FALSE);
        gtk_widget_show(GTK_WIDGET(header_box));
        gtk_widget_show(GTK_WIDGET(sidebar_overlay));
        gtk_widget_hide(GTK_WIDGET(go_chats));
        gtk_widget_show(Send_button);
        gtk_widget_hide(Delete_button);
        gtk_entry_set_placeholder_text(GTK_ENTRY(Message_Box), "Type your message");
        g_signal_connect(G_OBJECT(Message_Box), "activate", send_message, NULL);
    }
    
}


void scrolling()
{
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(Scroll));
    gtk_adjustment_set_page_size (adj, 0);
    double value = gtk_adjustment_get_upper(adj);
    gtk_adjustment_set_value(adj, value);
}



void pre_delete_user() {

    if (gtk_widget_get_visible(new_password) == true) {
        gtk_widget_hide(new_password);
    }
    if (gtk_widget_get_visible(error_box2) == true) {
        gtk_widget_hide(error_box2);
    }
    
    // gtk_widget_set_can_focus (message_button, true);
    // gtk_widget_grab_focus(message_button);
    gtk_widget_show (Confirm);
}

void pre_change_password() {
   gtk_widget_show (new_password);
}

void change_lang() {

    if (gtk_widget_get_visible(new_password) == true) {
        gtk_widget_hide(new_password);
    }
    if (gtk_widget_get_visible(error_box2) == true) {
        gtk_widget_hide(error_box2);
    }
    pthread_t conf;
    if (Config.localization == 0) {
        Config.localization = 1;
        pthread_create(&conf, NULL, pre_update_config, NULL);
    }
    else if (Config.localization == 1) {
        Config.localization = 0;
        pthread_create(&conf, NULL, pre_update_config, NULL);
    }
}

void notify() {
    if (gtk_widget_get_visible(new_password) == true) {
        gtk_widget_hide(new_password);
    }
    if (gtk_widget_get_visible(error_box2) == true) {
        gtk_widget_hide(new_password);
    }
    pthread_t conf;
    if (Config.notifications== 0) {
        Config.notifications = 1;
        pthread_create(&conf, NULL, pre_update_config, NULL);
    }
    else if (Config.notifications == 1) {
        Config.notifications = 0;
        pthread_create(&conf, NULL, pre_update_config, NULL);
    }
}

