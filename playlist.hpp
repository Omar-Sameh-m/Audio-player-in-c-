#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iomanip>
#include "shaikh.cpp"
using namespace std;
using namespace sf;
class Doubly_linked_list
{
private:
//minus
   Shaikh *head;
   Shaikh *tail;  
   Surah *currentSurah;
   Music player;

public:
//plus
   Doubly_linked_list()
   {
      head = nullptr;
      tail = nullptr;
      
      currentSurah = nullptr;
   }
   void add_playlist(string shaikhName)
   {
      Shaikh *newshaikh = new Shaikh(shaikhName);
      if (head == nullptr)
      {
         head = tail = newshaikh;
         newshaikh->next = newshaikh->prev = nullptr;
      }
      else
      {
         newshaikh->next = nullptr;
         newshaikh->prev = tail;
         tail->next = newshaikh;
         tail = newshaikh;
      }
   }
   void add_surah(string shaikhName, string surahName, string dire, string type)
   {

      Shaikh *tempShaikh = head;
      // check if shaikh is already exist
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }
      if (tempShaikh == nullptr)
      {
         cout << "this playlist does not exist\n";
         return;
      }

      Surah *tempSurah = tempShaikh->headSurah;
      // check if surah is already exist
      while (tempSurah != nullptr)
      {
         if (tempSurah->surahName == surahName)
         {
            cout << "surah already exist\n";
            return;
         }
         // to stay in the last node ande ignore to be null
         if (tempSurah->next == nullptr)
            break;
         tempSurah = tempSurah->next;
      }
      Surah *newSurah = new Surah(surahName);
      newSurah->director = dire;
      newSurah->type = type;
      // add at first
      if (tempSurah == nullptr)
      {
         tempShaikh->headSurah = newSurah;
      }
      else
      {
         // add to last surah
         tempSurah->next = newSurah;
         newSurah->prev = tempSurah;
      }
   }
   void modifyPosition(string shaikhName, string suarhName, int pos)
   {
      Shaikh *tempShaikh = head;
      // بحث اسم الشيخ زي كل اللي قبله
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }
      if (tempShaikh == nullptr)
      {
         cout << "this playlist does not exist\n";
         return;
      }
      Surah *tempSurah = tempShaikh->headSurah;
      Surah *requiredSurah = nullptr;
      while (tempSurah != nullptr)
      {
         if (tempSurah->surahName == suarhName)
         {
            // لو لقينا السورة اللي عايزينها هنخزنها و نطلع برا اللوب
            requiredSurah = tempSurah;
            break;
         }
         tempSurah = tempSurah->next;
      }
      // نختبر هل لقيناها و طلعنا ولا طلعنا لما اللوب خلصت
      if (requiredSurah == nullptr)
      {
         cout << "surah does not exist\n";
      }
      else
      {
         // لو هنحطها في البداية
         if (pos == 1)
         {
            if (requiredSurah == tempShaikh->headSurah)
               return;
            // لو السورة بعدها سورة يعني مش الاخيرة
            if (requiredSurah->next != nullptr)
            {

               // نكست اللي قبلها هيشاور علي النكست بتاعها
               requiredSurah->prev->next = requiredSurah->next;
               // بريف اللي بعدها هيشاور علي البريف بتاعها
               requiredSurah->next->prev = requiredSurah->prev;
            }
            else
            {
               requiredSurah->prev->next = nullptr;
            }
            // نكست السورة المطلوبة هو بداية السور
            requiredSurah->next = tempShaikh->headSurah;
            // بريف البداية هو السورة المطلوبة
            tempShaikh->headSurah->prev = requiredSurah;
            // السور المطلوبة بقت في البداية
            tempShaikh->headSurah = requiredSurah;
            requiredSurah->prev = nullptr;
         }
         else
         {
            // عداد عشان نوصل للموقع
            int counter = 1;
            tempSurah = tempShaikh->headSurah;

            Surah *prevSurah = nullptr;
            // لحد ما تنتهي او نوصل الموقع
            while (tempSurah != nullptr && counter < pos)
            {
               prevSurah = tempSurah;
               tempSurah = tempSurah->next;
               counter++;
            }
            // لو طلعنا بسبب ان وصلنا للنهاية و مش وصلنا الموقع فهنحط السورة في الاخر
            if (tempSurah == nullptr)
            {

               if (requiredSurah == tempShaikh->headSurah)
               {
                  // لو فيه قبلها نربط باللي بعدها
                  tempShaikh->headSurah = tempShaikh->headSurah->next;
                  tempShaikh->headSurah->prev = nullptr;
               }
               if (requiredSurah == prevSurah) // معناها انها الاخيرة
               {
                  return;
               }
               if (requiredSurah->prev!=nullptr)
               {
                  requiredSurah->prev->next = requiredSurah->next;
               }
               requiredSurah->next->prev = requiredSurah->prev;
               
               // نربط الاخيرة بالمطلوبة
               prevSurah->next = requiredSurah;
               // المطلوبة يسبقها الاخيرة
               requiredSurah->prev = prevSurah;
               // مفيش حاجة بعد المطلوبة يعني الاخيرة
               requiredSurah->next = nullptr;
            }

            else
            // اخر حالة لو وصلنا للموقع المطلوب
            {
               if (requiredSurah->next != nullptr)
               {
                  // ربط اللي بعدها باللي قبها
                  requiredSurah->next->prev = requiredSurah->prev;
               }
               if (requiredSurah->prev != nullptr)
               {
                  // ربط اللي قبلها باللي بعدها
                  requiredSurah->prev->next = requiredSurah->next;
               }
               // نحطها بعد اخر سورة وصلناها
               requiredSurah->prev = prevSurah;
               // نربط اخر واحدة وصلناها بالمطلوبة
               prevSurah->next = requiredSurah;
               // نربط المطلوبة بالسور اللي بعد كدا
               requiredSurah->next = tempSurah;
               // نربط باقي السور بالمطلوبة
               tempSurah->prev = requiredSurah;
            }
         }
      }
   }
   void saveToFile()
   {
      ofstream outFile;
      outFile.open("data.txt", ios::app); // بنكمل كتابة مش بنمسح اللي فات
      if (!outFile.is_open())
      {
         cout << "Failed to open file for writing\n";
         return;
      }

      Shaikh *tempShaikh = head;
      while (tempShaikh != nullptr)
      {
         // كتابة اسم الشيخ
         outFile << "Playlist: " << tempShaikh->shaikh_name << "\n";

         // كتابة معلومات السور
         Surah *tempSurah = tempShaikh->headSurah;
         while (tempSurah != nullptr)
         {
            outFile << tempSurah->surahName << " | "
                    << tempSurah->type << " | "
                    << tempSurah->director << "\n";
            tempSurah = tempSurah->next;
         }

         // النهاية
         outFile << "END\n";

         tempShaikh = tempShaikh->next;
      }

      outFile.close();
      cout << "Data saved successfully to data.txt\n";
   }
   void loadFrom()
   {
      ifstream inFile;
      inFile.open("data.txt", ios::in);
      if (!inFile.is_open())
      {
         cout << "Failed to open file for reading\n";
         return;
      }

      string line, shaikhName, surahName, type, director;

      while (getline(inFile, line))
      {
         if (line.find("Playlist: ") == 0)
         {
            // طلعلي اسم الشيخ من نهاية اول الكلمة دي لنهاية السطر
            shaikhName = line.substr(10);
            add_playlist(shaikhName);
         }
         else if (line == "END")
         {
            // نهاية بيانات الشيخ الحالي، انتقل للشيخ التالي
            continue;
         }
         else
         {
            // الموقع الاول من الشمال لليمين
            int pos1 = line.find(" | ");
            // التاني من اليمين للشمال
            int pos2 = line.rfind(" | ");
            // عشان مش نكرر نفس الموقع
            //  لو المواقع موجودة و مش بتساوي بعض
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
            {
               surahName = line.substr(0, pos1);
               // هبدء من الموقع كذا و همشي كام خطوة
               type = line.substr(pos1 + 3, pos2 - pos1 - 3);
               director = line.substr(pos2 + 3);

               add_surah(shaikhName, surahName, director, type);
            }
         }
      }

      inFile.close();
      cout << "Data loaded successfully from data.txt\n";
   }
   void printPlayList()
   {
      if (head == nullptr)
      {
         cout << "No playlists exist.\n";
         return;
      }

      Shaikh *tempShaikh = head;
      int id = 1;
      cout << "===========================================\n";
      cout << "|           Current Playlists          |\n";
      cout << "===========================================\n";
      while (tempShaikh != nullptr)
      {
         cout << "| " << setw(3) << id << ". " << setw(30) << left << tempShaikh->shaikh_name << " |\n";
         tempShaikh = tempShaikh->next;
         id++;
      }
      cout << "===========================================\n";
   }
   void printSurahs(string shaikhName)
   {
      // البحث عن الشيخ
      Shaikh *tempShaikh = head;
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }

      if (tempShaikh == nullptr)
      {
         cout << "This playlist does not exist.\n";
         return;
      }

      // عرض السور الخاصة بالشيخ
      if (tempShaikh != nullptr)
      {
         Surah *tempSurah = tempShaikh->headSurah;
         cout << "===========================================\n";
         cout << "| Playlist: " << left << setw(30) << tempShaikh->shaikh_name << " |\n";
         cout << "===========================================\n";
         while (tempSurah != nullptr)
         {
            cout << "| Surah: " << setw(20) << left << tempSurah->surahName
                 << "| Type: " << setw(20) << left << tempSurah->type
                 << "| Director: " << setw(20) << left << tempSurah->director << " |\n";
            tempSurah = tempSurah->next;
         }
         cout << "===========================================\n";
      }
   }
   void removePlayList(string shaikhName)
   {
      Shaikh *tempShaikh = head;
      // check if exist
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }

      if (tempShaikh == nullptr)
      {
         cout << "This playlist does not exist\n";
         return;
      }
      // if is head
      if (tempShaikh == head)
      {
         head = head->next;
         // check if is tail
         if (head != nullptr)
         {
            head->prev = nullptr;
         }
         else
         {
            tail = nullptr;
         }
      }
      // if is tail
      else if (tempShaikh->next == nullptr)
      {
         tail = tempShaikh->prev;
         tail->next = nullptr;
      }
      // in other position
      else
      {
         tempShaikh->prev->next = tempShaikh->next;
         tempShaikh->next->prev = tempShaikh->prev;
      }
      // delete releated surahs
      Surah *tempSurah = tempShaikh->headSurah;
      while (tempSurah != nullptr)
      {
         Surah *nextSurah = tempSurah->next;
         delete tempSurah;
         tempSurah = nextSurah;
      }

      delete tempShaikh;
   }
   void removeSurah(string shaikhName, string SurahName)
   {
      Shaikh *tempShaikh = head;
      // check if shaikh exist
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }

      if (tempShaikh == nullptr)
      {
         cout << "This playlist does not exist\n";
         return;
      }
      Surah *tempSurah = tempShaikh->headSurah;
      // check if surah exist
      while (tempSurah != nullptr && tempSurah->surahName != SurahName)
      {
         tempSurah = tempSurah->next;
      }
      if (tempSurah == nullptr)
      {
         cout << "this surah does not exist\n";
         return;
      }
      else
      {
         // if have prev it means is not the head
         if (tempSurah->prev != nullptr)
         {
            tempSurah->prev->next = tempSurah->next;
         }
         // is the head
         else
         {
            // move head suarh in shaikh to the next
            tempShaikh->headSurah = tempShaikh->headSurah->next;
         }
         // if have next it means is not the tail
         if (tempSurah->next != nullptr)
         {
            tempSurah->next->prev = tempSurah->prev;
         }
         delete tempSurah;
      }
   }
   void playShaikhSurahs(string shaikhName)
   {
      // اختبار لو الشيخ موجود كالعادة
      Shaikh *tempShaikh = head;
      while (tempShaikh != nullptr && tempShaikh->shaikh_name != shaikhName)
      {
         tempShaikh = tempShaikh->next;
      }
      // لو مش لقينا الشيخ او السورة
      if (tempShaikh == nullptr || tempShaikh->headSurah == nullptr)
      {
         cout << "shaikh does not exist or no surahs\n";
         return;
      }
      // لو لقيناهم نحطهم في الكرنت
      currentSurah = tempShaikh->headSurah;
      // الدالة دي بتاخد string للمسار اللي هتشغله
      player.openFromFile(currentSurah->director);
      // دالة التسغيل
      player.play();
      cout << "playing: " << currentSurah->surahName << endl;
   }
   void playNextSurah()
   {
      // نختبر انها مش الاخير
      if (currentSurah != nullptr && currentSurah->next != nullptr)
      {
         // نحرك للسورة اللي بعدها
         currentSurah = currentSurah->next;
         StopCurrentSurah();
         player.openFromFile(currentSurah->director);
         player.play();
         cout << "playing: " << currentSurah->surahName << endl;
      }
      else
      {
         cout << "this last surah in playlist\n";
      }
   }
   void playPreviousSurah()
   {
      // نختبر انها مش الاولي
      if (currentSurah != nullptr && currentSurah->prev != nullptr)
      {
         // نحرك للي قبله
         currentSurah = currentSurah->prev;
         StopCurrentSurah();
         player.openFromFile(currentSurah->director);
         player.play();
         cout << "playing: " << currentSurah->surahName << endl;
      }
      else
      {
         cout << "this the first surah in playlist\n";
      }
   }
   void pauseCurrentSurah()
   {
      // نختبر الحالة لو شغال نوقف
      if (player.getStatus() == Music::Playing)
      {
         // دالة الايقاف المؤقت
         player.pause();
         cout << "surah was paused\n";
      }
   }
   void resumeCurrentSurah()
   {
      // نختبر الحالة واقف نشغل
      if (player.getStatus() == Music::Paused)
      {
         player.play();
         cout << "surah was resumed\n";
      }
   }
   void StopCurrentSurah()
   {
      // لو  الصوت مش واقف
      if (player.getStatus() != Music::Stopped)
      {
         // نوقف الصوت ده مش ايقاف موقت لو شغلنا الصوت تاني بيبدء من الاول
         player.stop();
         cout << "suarh was stoped\n";
      }
   }
   void printAllData()
   {
      if (head == nullptr)
      {
         cout << "No playlists available.\n";
         return;
      }

      Shaikh *tempShaikh = head;
      int id = 1;
      while (tempShaikh != nullptr)
      {
         cout << "===========================================\n";
         cout << "| Playlist " << setw(2) << id << ": " << left << setw(30) << tempShaikh->shaikh_name << " |\n";
         cout << "===========================================\n";

         Surah *tempSurah = tempShaikh->headSurah;
         while (tempSurah != nullptr)
         {
            cout << "| Surah: " << setw(20) << left << tempSurah->surahName
                 << "| Type: " << setw(20) << left << tempSurah->type
                 << "| Director: " << setw(20) << left << tempSurah->director << " |\n";
            tempSurah = tempSurah->next;
         }

         cout << "===========================================\n";
         tempShaikh = tempShaikh->next;
         id++;
      }
   }
       ~Doubly_linked_list()
   {
      while (head != nullptr)
      {
         Surah *tempSurah = head->headSurah;
         while (tempSurah != nullptr)
         {
            Surah *nextSurah = tempSurah->next;
            delete tempSurah;
            tempSurah = nextSurah;
         }
         Shaikh *nextShaikh = head->next;
         delete head;
         head = nextShaikh;
      }
   }
};

#endif
