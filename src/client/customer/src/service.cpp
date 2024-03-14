#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    int flag = -2;
    while(run){
        int comand = kwd.GetComandId();

        flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){
            run = false;
        }
        if(flag >= 0){
            break;
        }
    }
    return flag;
}

int MainService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Search product", "Visualize orders", "Exit"};
    Kwd_Man kwm = Kwd_Man(keywords);
    while(run){
        int comand = kwm.GetComandId();

        int flag = ManageMainKwd(ctx, comand);

        if(flag == -1){
            run = false;
            break;
        }
    }
    return 0;
}

int SearchProduct(Context ctx){
    system("clear");
    cout << "Product name: ";
    string name;
    getline(cin, name);

    bool run = true;
    while(run){
        system("clear");
        cout << "\"" << name << "\"" << endl << endl;
        vector<Insertion> insertions = GetProductList(ctx, name);
        vector<string> keywords;
        int max = 0;
        int price_max = 0;
        for(long unsigned int i = 0; i < insertions.size(); i++){
            int len = insertions[i].GetName().length();
            int price_len = to_string(insertions[i].GetPrice()).length();
            if(len > max){max = len;}
            if(price_len > price_max){price_max = price_len;}
        }
        max += 5;
        for(long unsigned int i = 0; i < insertions.size(); i++){
            keywords.push_back(insertions[i].ToString(max, price_max));
        }
        keywords.push_back("Back");
        V_Kwd_Man vkwm = V_Kwd_Man(keywords);
        long unsigned int id = vkwm.GetComandId("Select a product\n");

        if(id == insertions.size()){return 0;}
        VisualizeInsertion(ctx, insertions[id]);
    }
    return 0;
}

int VisualizeInsertion(Context ctx, Insertion ins){
    while(true){
        system("clear");
        char buf[500];
        snprintf(buf, sizeof(buf), "%s\nPrice: %.2f $\n", ins.GetName().c_str(), ins.GetPrice());
        Kwd_Man kwd = Kwd_Man({"Buy", "Back"});
        int id = kwd.GetComandId(buf);
        if(id == 1){return 0;}
        CreatingOrderService(ctx, ins); 
    }
    return 0;
}

int CreatingOrderService(Context ctx, Insertion ins){
    system("clear");
    char buf[500];
    snprintf(buf, sizeof(buf), "%s\nPrice: %.2f $\n\nSelect quantity: ", ins.GetName().c_str(), ins.GetPrice());
    Spinner sp = Spinner(false);
    int quantity = sp.GetQuantity(buf);
    
    Kwd_Man kwd = Kwd_Man({"Yes", "No"});
    snprintf(buf, sizeof(buf), "%s\nQuantity: %d\n\nTotal price: %.2f\n\nConfirm order?",
    ins.GetName().c_str(), quantity, ins.GetPrice()*quantity);
    int id = kwd.GetComandId(buf);
    if(id == 1){return 0;}

    bool created = CreateOrder(ctx, ins, quantity);
    if(created){Notification("Correctly created order");}
    else{Notification("Error while creating order");}
    return 0;
}

int VisualizeOrders(Context ctx){
    system("clear");
    //char buf[500];
    //snprintf(buf, sizeof(buf), 
    //"SELECT i.product i.price o.quantity s.shipping_status FROM orders o JOIN insertion i ON i.id = o.product JOIN shipping s ON s.number_order = o.id WHERE o.customer = %d AND s.shipping_status = %s");
    return 0;
}