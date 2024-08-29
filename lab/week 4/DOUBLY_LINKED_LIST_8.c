// You are tasked with managing a playlist of songs using a doubly linked list. Each song has a unique song_id, a title, and a duration (in seconds). Your task is to implement a function to split the playlist into two parts based on a given duration. The first part of the playlist should contain all songs with a duration less than or equal to the given duration, and the second part should contain all songs with a duration greater than the given duration. The function should modify the original playlist and return the head of the second part.

// Sample Input 1:

// 4

// 1

// Song A

// 180

// 2

// Song B

// 120

// 3

// Song C

// 240

// 4

// Song D

// 200

// 150

// Sample Output 1:

// The first part of the playlist

// 2 Song B 120

// The second part of the playlist

// 1 Song A 180

// 3 Song C 240

// 4 Song D 200

// Input Format

// Number of Songs in the Playlist: N (Integer)

// Songs: N lines, each containing the song_id (integer), title (string), and duration (integer).

// Split Duration: D (Integer) - The duration used to split the playlist.

// Constraints

// DONT CHANGE THE BOILER CODE.

// Output Format

// First Playlist: Print the songs in the first part of the playlist, sorted by their original order.

// Second Playlist: Print the songs in the second part of the playlist, sorted by their original order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
   int song_id;
   char title[256];
   int duration;
   struct Song* prev;
   struct Song* next;
} Song;

typedef struct {
   Song* head;
   Song* tail;
} Playlist;

// Function prototypes
Playlist* createPlaylist();
void addSong(Playlist* playlist, int song_id, const char* title, int duration);
Song* splitPlaylist(Playlist* playlist, int duration);
void printPlaylist(Playlist* playlist);
void freePlaylist(Playlist* playlist);

int main() {
   int N;
   scanf("%d", &N);
    Playlist* playlist = createPlaylist();
    for (int i = 0; i < N; i++) {
       int song_id, duration;
       char title[256];
       scanf("%d", &song_id);
       getchar(); // Consume the newline character
       fgets(title, 256, stdin);
       title[strcspn(title, "\n")] = '\0'; // Remove newline character
       scanf("%d", &duration);
       addSong(playlist, song_id, title, duration);
   }
    int D;
   scanf("%d", &D);
   Song* secondPartHead = splitPlaylist(playlist, D);
    // Print the first playlist
   printf("The first part of the playlist\n");
   printPlaylist(playlist);
    // Print the second part
   Playlist secondPart = { secondPartHead, NULL };
   printf("The second part of the playlist\n");
   printPlaylist(&secondPart);
    // Free memory
   freePlaylist(playlist);
   freePlaylist(&secondPart);
    return 0;
}

// Create a new playlist
Playlist* createPlaylist() {
   Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
   playlist->head = NULL;
   playlist->tail = NULL;
   return playlist;
}

// Add a song to the playlist
void addSong(Playlist* playlist, int song_id, const char* title, int duration) {
   Song* newSong = (Song*)malloc(sizeof(Song));
   newSong->song_id = song_id;
   strncpy(newSong->title, title, sizeof(newSong->title));
   newSong->duration = duration;
   newSong->prev = NULL;
   newSong->next = NULL;

   if (playlist->head == NULL) {
       playlist->head = playlist->tail = newSong;
   } else {
       playlist->tail->next = newSong;
       newSong->prev = playlist->tail;
       playlist->tail = newSong;
   }
}

// Split the playlist based on the given duration
Song* splitPlaylist(Playlist* playlist, int duration) {
    Playlist secondPartPlaylist = { NULL, NULL };
    Song* current = playlist->head;
 
    while (current != NULL) {
        Song* next = current->next;
        if (current->duration > duration) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                playlist->head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                playlist->tail = current->prev;
            }
            if (secondPartPlaylist.head == NULL) {
                secondPartPlaylist.head = secondPartPlaylist.tail = current;
                current->prev = NULL;
                current->next = NULL;
            } else {
                secondPartPlaylist.tail->next = current;
                current->prev = secondPartPlaylist.tail;
                secondPartPlaylist.tail = current;
                current->next = NULL;
            }
        }
        current = next;
    }
    return secondPartPlaylist.head;  // Return the head of the second part
}
 
// Print all songs in the playlist
void printPlaylist(Playlist* playlist) {
    Song* current = playlist->head;
    while (current != NULL) {
        printf("%d %s %d\n", current->song_id, current->title, current->duration);
        current = current->next;
    }
}

// Free all nodes in the list
void freePlaylist(Playlist* playlist) {
   Song* current = playlist->head;
   Song* next;
   while (current != NULL) {
       next = current->next;
       free(current);
       current = next;
   }
}