typedef struct date
{
    int day;
    int month;
    int year;

} Date;

typedef struct room
{
    int room_no;
    char type[20];
    float price;

} Room;

typedef struct guest
{
    int ID;
    int people;
    char name[26];
    int room_no;
    int bill_status;
    Date check_in;
    Date check_out;
    struct guest *next;

} Guest;

void load_guests_from_file(Guest **head, int *gc);
void save_guests_to_file(Guest **head);
void admin_menu(Guest **head, int *gc);
void view_guests(Guest **head);
void search_guest(Guest **head);
void clear_all_guests(Guest **head, int *gc);
void guest_menu(Guest **head, int *gc);
void book_room(Guest **head, int *gc);
void check_out(Guest **head, int *gc);
void pay_bill(Guest **head);
int checkifclash(Date d1, Date d2, Date d3, Date d4);
int checkifvalidDate(Date date);