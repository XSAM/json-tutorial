#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */
#include "leptjson.h"

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_literal(lept_context* c, lept_value* v, const char* ch, int expect_result)
{
    char* p = ch;
    while(*p != '\0')
    {
        if(*c->json == *p)
        {
            p++;
            c->json++;
            continue;
        }
        else
        {
            return LEPT_PARSE_INVALID_VALUE;
        }
    }
    v->type = expect_result;
    return LEPT_PARSE_OK;
}

static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    return lept_parse_literal(c, v, "ull", LEPT_NULL);
}

static int lept_parse_true(lept_context* c, lept_value* v)
{
    EXPECT(c, 't');
    return lept_parse_literal(c, v, "rue", LEPT_TRUE);
}

static int lept_parse_false(lept_context* c, lept_value* v)
{
    EXPECT(c, 'f');
    return lept_parse_literal(c, v, "alse", LEPT_FALSE);
}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case 't': return lept_parse_true(c, v);
        case 'f': return lept_parse_false(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    int ret = lept_parse_value(&c, v);
    if(ret == LEPT_PARSE_OK)
    {
        lept_parse_whitespace(&c);
        if(*c.json != '\0')
        ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
