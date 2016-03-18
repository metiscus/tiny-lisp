#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Field Field;

typedef enum FieldType
{
    TYPE_BOOLEAN,
    TYPE_INTEGER,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_OBJECT
} FieldType;

struct Field
{
    uint32_t size;
    FieldType type;
    char *name;
    union {
        struct { bool boolean; };
        struct { int32_t integer; };
        struct { double  real; };
        struct { char* string; };
        struct { uint32_t object; };
    };
};



void field_free(Field* field)
{
    if(field)
    {
        if(field->type == TYPE_STRING)
        {
            if(field->string)
            {
                free(field->string);
            }
        }
        free(field);
    }
}

typedef struct Object Object;

struct Object
{
    uint32_t id;
    uint32_t field_count;
    Field **fields;
};


Object* object_new(uint32_t id)
{
    Object *obj = (Object*)calloc(1, sizeof(Object));
    assert(obj);
    return obj;
}

void object_free(Object *obj)
{
    if(obj)
    {
        uint32_t i;
        for(i=0; i<obj->field_count;++i)
        {
            field_free(obj->fields[i]);
        }

        free(obj);
    }
}

Field* object_get_field(Object *obj, char* name)
{
    assert(obj);
    assert(name);
    uint32_t i;
    for(i=0; i<obj->field_count; ++i)
    {
        if(strcmp(name, obj->fields[i]->name) == 0)
        {
            return obj->fields[i];
        }
    }
    return NULL;
}
