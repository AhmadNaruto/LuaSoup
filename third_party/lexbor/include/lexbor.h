#ifndef LEXBOR_H
#define LEXBOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Official Lexbor HTML / CSS Engine C API Definitions
typedef struct lxb_html_document lxb_html_document_t;
typedef struct lxb_html_parser lxb_html_parser_t;
typedef struct lxb_css_parser lxb_css_parser_t;

lxb_html_parser_t* lxb_html_parser_create(void);
lxb_html_document_t* lxb_html_parse(lxb_html_parser_t* parser, const unsigned char* html, size_t size);
void lxb_html_document_destroy(lxb_html_document_t* document);

#ifdef __cplusplus
}
#endif

#endif // LEXBOR_H
