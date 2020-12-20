#include "lstm.h"
void printHelp();
int main(int argc, char *argv[])
{
    char action = 'x', role = 'x';
    int epochsT = 1, epochsP = 1, peopleNum = 1, ch;
    bool Role;
    if (argc == 1)
    {
        cout << "Use \"lstm -h\" to get help.\n" << endl;
        do
        {
            cout << "\nInput your role:\n(1)SERVER  (2)CLIENT\nrole:" << flush;
            cin.get(role).get();
        } while (role != '1' && role != '2');
        do
        {
            cout << "\nInput your action:\n(1)Triples Gen   (2)Triples Check   (3)Share Gen   (4)LSTM\naction:"
                 << flush;
            cin.get(action).get();
        } while (action != '1' && action != '2' && action != '3' && action != '4');
        Role = (role == '1') ? SERVER : CLIENT;
    } else
    {
        while ((ch = getopt(argc, argv, "r:a:p:h")) != -1)
        {
            switch (ch)
            {
                case 'r':
                    Role = (!strcmp(optarg, "1")) ? SERVER : CLIENT;
                    break;
                case 'a':
                    action = optarg[0];
                    break;
                case 'p':
                    peopleNum = stoi(optarg);
                    break;
                case '?':
                    printf("unknow option:%c\n", optopt);
                    break;
                case 'h':
                default:
                    printHelp();
                    return 0;
            }
        }
    }
    cout << "\nYou are " << ((Role == SERVER) ? "SERVER" : "CLIENT") << endl;

    Lstm lstm(Role, peopleNum);

    switch (action)
    {
        case '1':
            cout << "Triples Gen" << endl;
            cout << "\nInput training rounds:" << flush;
            cin >> epochsT;
            cin.get();
            cout << "\nInput predict rounds:" << flush;
            cin >> epochsP;
            cin.get();
            lstm.triplesGen(epochsT,epochsP);
            break;
        case '2':
            cout << "Triples Check" << endl;
            check();
            break;
        case '3':
            cout << "Share Gen" << endl;
            shareGen();
            break;
        case '4':
            cout << "LSTM" << endl;
            lstm.train();
            break;
        default:
            exit(1);
    }
    showTime(1);
    return 0;
}
void printHelp(){
    cout << "\n Usage :"
         << "\tlstm [Options] <Destination>\n\n"
         << " Options      Destination\n"
         << "  -r          (1)SERVER        (2)CLIENT\n"
         << "  -a          (1)Triples Gen   (2)Triples Check   (3)Share Gen   (4)LSTM\n"
         << "  -p          Number of people, input an interger.\n"
         << "  -h          Help\n"
         << endl;
}