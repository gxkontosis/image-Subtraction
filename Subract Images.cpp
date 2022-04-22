#include <iostream>
#include <fstream>
#include <vector>
#include <future>

using namespace std;

class loadData {
public:
    string imagePath;
    short value{};
    char buf[sizeof(short)]{};

    vector<short> results;

    loadData() {

        cout << "Please enter Image path: " << endl;
        cin >> imagePath;

    }

    void readImg() {
        ifstream myData(imagePath, ios::binary);

        while (myData.read(buf, sizeof(short)))
        {
            memcpy(&value, buf, sizeof(value));
            results.push_back(value);
        }
    }
};

int main()
{
    loadData Image1;
    auto future1 = std::async(std::launch::async, [&] {Image1.readImg(); });
    
    loadData Image2;
    auto future2 = std::async(std::launch::async, [&] {Image2.readImg(); });

    future1.wait();
    future2.wait();
   
    vector<char> results;

    if(Image1.results.size() == Image2.results.size())
    for (int i = 0; i < Image1.results.size(); i++) {
        short res = Image1.results[i] - Image2.results[i];
        if (res < 0) { res = 0; }
        cout << res << " ";
        results.push_back(res);
    }

    ofstream finalImage("Image3.raw", ios::out | ios::binary);
    finalImage.write((char*)&results, sizeof(results));
    finalImage.close();

    return 0;
}