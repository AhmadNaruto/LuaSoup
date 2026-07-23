#include "lexbor.h"
#include <stdlib.h>

lxb_html_parser_t* lxb_html_parser_create(void) {
    return NULL;
}

lxb_html_document_t* lxb_html_parse(lxb_html_parser_t* parser, const unsigned char* html, size_t size) {
    (void)parser; (void)html; (void)size;
    return NULL;
}

void lxb_html_document_destroy(lxb_html_document_t* document) {
    (void)document;
}
