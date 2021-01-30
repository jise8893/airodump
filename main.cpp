#include <iostream>
#include <cstdio>
#include <pcap.h>
#include <map>
#include <string>
#include <curses.h>
#include <unistd.h>
#include "dot11_frame.h"
#include "airodump.h"
#include "extended_radiotap.h"
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

}

//beacons, pwr,essid
void insert_container(std::map<class Mac,class airodump>& container,const u_char* packet){
    Ieee80211_radiotap_header * radiotab;
    Dot11_frame * frame;

    radiotab=(Ieee80211_radiotap_header *)(packet);
    Extended_radiotap *ext_radio=(Extended_radiotap*)(packet+radiotab->it_len-sizeof(Extended_radiotap));

    frame=(Dot11_frame *)(packet+radiotab->it_len);
   if(frame->frame_control.subtype==0x0008){
     for(auto bssid=container.begin(); bssid!=container.end(); bssid++){
        if(memcmp(frame->address_3,bssid->first,6)==0)
        {
            bssid->second.pwr=256-ext_radio->antenna_signal;
            if(frame->frame_control.subtype==0x0008)
                   bssid->second.beacons++;
            return;
            }
     }

          airodump content;
          content.pwr=256-ext_radio->antenna_signal;
          content.beacons=1;
          memcpy(content.essid, packet+sizeof(Dot11_frame)+radiotab->it_len, frame->tag_length);
          content.len=frame->tag_length;

          container.insert(std::make_pair(frame->address_3,content));
       }
}


template <typename K,typename V>
void print_list(std::map<K,V>& container){

    for(auto itr=container.begin(); itr!=container.end(); itr++){
        hextomac(itr->first);
        printf("\t pwr: -%d beacons: %d ESSID: ",itr->second.pwr,itr->second.beacons);
        for(int i=0; i<itr->second.len; i++){
            printf("%c",itr->second.essid[i]);
        }
        printf("\n");
    }

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
       // printf("Catched packet length [%d]\n",header->caplen);
        insert_container(container,packet);

        printf("BSSID \t\t\t PWR \t   Beacons    ESSID \n\n");
        print_list(container);

       printf("size:%d\n",container.size());
    }

    return 0;
}
