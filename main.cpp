#include <iostream>
#include <cstdio>
#include <pcap.h>
#include <map>
#include <string>
#include <curses.h>
#include <unistd.h>
#include "dot11_frame.h"
#include "airodump.h"
void usage(){
    printf("syntx  : airodump <interface>\n");
    printf("example: airodump wlan0\n");
}
void hextomac(uint8_t * address){

    unsigned char mac[6];
    memcpy(mac,address,6);
    for(int i=0 ; i<6; i++){
        printf("%02x",mac[i]);
        if(i!=5){
            printf(":");
        }
    }
     printf("\n");
}
//beacons, pwr,essid
void insert_container(std::map<class Mac,class airodump>& container,const u_char* packet){
    Ieee80211_radiotap_header * radiotab;
    Dot11_frame * frame;

    radiotab=(Ieee80211_radiotap_header *)(packet);

    frame=(Dot11_frame *)(packet+radiotab->it_len);
    if(frame->frame_control.type==0){ //CHECK management frame
       auto bssid = container.find(frame->address_3);

       if(bssid!=container.end()){
         bssid->second.pwr=256-radiotab->antenna_signal;
         if(frame->frame_control.subtype==0x0008)
                bssid->second.beacons++;

       }else{
          airodump content;
          content.pwr=256-radiotab->antenna_signal;
          content.beacons=0;
          memcpy(content.essid,packet+sizeof(Dot11_frame)+radiotab->it_len+frame->tag_length,frame->tag_length);
          if(frame->frame_control.subtype==0x0008)
            bssid->second.beacons++;
           container.emplace(frame->address_3,content);
       }
    }

   // printf("pwr : [-%d]\n", 256-radiotab->antenna_signal);

}
template <typename K,typename V>
void print_list(std::map<K,V>& container){
    printf("BSSID \t\t ESSID \t\t PWR \t Beacons\n");
    int p=0;
    for(auto itr=container.begin(); itr!=container.end(); ++itr){
       hextomac(itr->first);

        fflush(stdout);
        p++;
    }
    printf("\n count: %d\n",p);
//    printf("\x1b[%dA",1+p);
}


int main(int argc,char* argv[])
{

    pcap_t *handle;
    const u_char* packet;
    char errbuf[PCAP_BUF_SIZE];
    pcap_pkthdr* header;

    std::map<class Mac,class airodump> container;

    if(argc!=2){
        usage();
        return -1;
    }
    handle=pcap_open_live(argv[1],BUFSIZ,1,1,errbuf);
    if(handle==nullptr){
        fprintf(stderr,"%s",errbuf);
    }

    while(true){
        int res=pcap_next_ex(handle,&header,&packet);
        if(res==0||res==-1||res==-2){
            continue;
        }
     //   printf("Catched packet length [%d]\n",header->caplen);
        insert_container(container,packet);
        print_list(container);
    }

    return 0;
}
