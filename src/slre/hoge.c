#include <stdio.h>
#include <string.h>

#include "slre.h"


int main(){
    printf("kusoga\n");
    const char *request = "\r\n\r\n";
    struct slre_cap caps[4];

    if (slre_match("^\\s+$",
                               request, strlen(request), caps, 4, 0) > 0) {
          printf("Method: [%.*s], URI: [%.*s]\n",
                           caps[0].len, caps[0].ptr,
                                    caps[1].len, caps[1].ptr);
    } else {
          printf("Error parsing [%s]\n", request);
    }
}
