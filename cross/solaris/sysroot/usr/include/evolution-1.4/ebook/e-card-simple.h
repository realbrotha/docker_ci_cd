/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Authors:
 *   Chris Lahey <clahey@ximian.com>
 *   Arturo Espinosa
 *   Nat Friedman (nat@ximian.com)
 *
 * Copyright (C) 2000 Ximian, Inc.
 * Copyright (C) 1999 The Free Software Foundation
 */

#ifndef __E_CARD_SIMPLE_H__
#define __E_CARD_SIMPLE_H__

#include <time.h>
#include <glib-object.h>
#include <stdio.h>
#include <ebook/e-card.h>
#include <ebook/e-card-types.h>
#include <e-util/e-list.h>

#define E_TYPE_CARD_SIMPLE            (e_card_simple_get_type ())
#define E_CARD_SIMPLE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), E_TYPE_CARD_SIMPLE, ECardSimple))
#define E_CARD_SIMPLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), E_TYPE_CARD_SIMPLE, ECardSimpleClass))
#define E_IS_CARD_SIMPLE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), E_TYPE_CARD_SIMPLE))
#define E_IS_CARD_SIMPLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), E_TYPE_CARD_SIMPLE))
#define E_CARD_SIMPLE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), E_TYPE_CARD_SIMPLE, ECardSimpleClass))

typedef enum _ECardSimplePhoneId ECardSimplePhoneId;
typedef enum _ECardSimpleEmailId ECardSimpleEmailId;
typedef enum _ECardSimpleAddressId ECardSimpleAddressId;
typedef enum _ECardSimpleType ECardSimpleType;
typedef enum _ECardSimpleField ECardSimpleField;

enum _ECardSimplePhoneId {
	E_CARD_SIMPLE_PHONE_ID_ASSISTANT,
	E_CARD_SIMPLE_PHONE_ID_BUSINESS,
	E_CARD_SIMPLE_PHONE_ID_BUSINESS_2,
	E_CARD_SIMPLE_PHONE_ID_BUSINESS_FAX,
	E_CARD_SIMPLE_PHONE_ID_CALLBACK,
	E_CARD_SIMPLE_PHONE_ID_CAR,
	E_CARD_SIMPLE_PHONE_ID_COMPANY,
	E_CARD_SIMPLE_PHONE_ID_HOME,
	E_CARD_SIMPLE_PHONE_ID_HOME_2,
	E_CARD_SIMPLE_PHONE_ID_HOME_FAX,
	E_CARD_SIMPLE_PHONE_ID_ISDN,
	E_CARD_SIMPLE_PHONE_ID_MOBILE,
	E_CARD_SIMPLE_PHONE_ID_OTHER,
	E_CARD_SIMPLE_PHONE_ID_OTHER_FAX,
	E_CARD_SIMPLE_PHONE_ID_PAGER,
	E_CARD_SIMPLE_PHONE_ID_PRIMARY,
	E_CARD_SIMPLE_PHONE_ID_RADIO,
	E_CARD_SIMPLE_PHONE_ID_TELEX,
	E_CARD_SIMPLE_PHONE_ID_TTYTDD,
	E_CARD_SIMPLE_PHONE_ID_LAST
};

/* We need HOME and WORK email addresses here. */
enum _ECardSimpleEmailId {
	E_CARD_SIMPLE_EMAIL_ID_EMAIL,
	E_CARD_SIMPLE_EMAIL_ID_EMAIL_2,
	E_CARD_SIMPLE_EMAIL_ID_EMAIL_3,
	E_CARD_SIMPLE_EMAIL_ID_LAST
};

/* Should this include (BILLING/SHIPPING)? */
enum _ECardSimpleAddressId {
	E_CARD_SIMPLE_ADDRESS_ID_BUSINESS,
	E_CARD_SIMPLE_ADDRESS_ID_HOME,
	E_CARD_SIMPLE_ADDRESS_ID_OTHER,
	E_CARD_SIMPLE_ADDRESS_ID_LAST
};

enum _ECardSimpleType {
	E_CARD_SIMPLE_TYPE_STRING,
	E_CARD_SIMPLE_TYPE_DATE,
	E_CARD_SIMPLE_TYPE_BOOL,
};

enum _ECardSimpleField {
	E_CARD_SIMPLE_FIELD_FILE_AS,
        E_CARD_SIMPLE_FIELD_FULL_NAME,
        E_CARD_SIMPLE_FIELD_EMAIL,
        E_CARD_SIMPLE_FIELD_PHONE_PRIMARY,
	E_CARD_SIMPLE_FIELD_PHONE_ASSISTANT,
        E_CARD_SIMPLE_FIELD_PHONE_BUSINESS,
        E_CARD_SIMPLE_FIELD_PHONE_CALLBACK,
        E_CARD_SIMPLE_FIELD_PHONE_COMPANY,
        E_CARD_SIMPLE_FIELD_PHONE_HOME,
        E_CARD_SIMPLE_FIELD_ORG,
        E_CARD_SIMPLE_FIELD_ADDRESS_BUSINESS,
        E_CARD_SIMPLE_FIELD_ADDRESS_HOME,
        E_CARD_SIMPLE_FIELD_PHONE_MOBILE,
        E_CARD_SIMPLE_FIELD_PHONE_CAR,
        E_CARD_SIMPLE_FIELD_PHONE_BUSINESS_FAX,
        E_CARD_SIMPLE_FIELD_PHONE_HOME_FAX,
        E_CARD_SIMPLE_FIELD_PHONE_BUSINESS_2,
        E_CARD_SIMPLE_FIELD_PHONE_HOME_2,
        E_CARD_SIMPLE_FIELD_PHONE_ISDN,
        E_CARD_SIMPLE_FIELD_PHONE_OTHER,
        E_CARD_SIMPLE_FIELD_PHONE_OTHER_FAX,
        E_CARD_SIMPLE_FIELD_PHONE_PAGER,
        E_CARD_SIMPLE_FIELD_PHONE_RADIO,
        E_CARD_SIMPLE_FIELD_PHONE_TELEX,
        E_CARD_SIMPLE_FIELD_PHONE_TTYTDD,
        E_CARD_SIMPLE_FIELD_ADDRESS_OTHER,
        E_CARD_SIMPLE_FIELD_EMAIL_2,
        E_CARD_SIMPLE_FIELD_EMAIL_3,
        E_CARD_SIMPLE_FIELD_URL,
        E_CARD_SIMPLE_FIELD_ORG_UNIT,
        E_CARD_SIMPLE_FIELD_OFFICE,
        E_CARD_SIMPLE_FIELD_TITLE,
        E_CARD_SIMPLE_FIELD_ROLE,
        E_CARD_SIMPLE_FIELD_MANAGER,
        E_CARD_SIMPLE_FIELD_ASSISTANT,
        E_CARD_SIMPLE_FIELD_NICKNAME,
        E_CARD_SIMPLE_FIELD_SPOUSE,
        E_CARD_SIMPLE_FIELD_NOTE,
        E_CARD_SIMPLE_FIELD_CALURI,
        E_CARD_SIMPLE_FIELD_FBURL,
        E_CARD_SIMPLE_FIELD_ICSCALENDAR,
	/* If you add after icscalendar, make sure to move LAST_SIMPLE_STRING */
	E_CARD_SIMPLE_FIELD_LAST_SIMPLE_STRING = E_CARD_SIMPLE_FIELD_ICSCALENDAR,
        E_CARD_SIMPLE_FIELD_ANNIVERSARY,
        E_CARD_SIMPLE_FIELD_BIRTH_DATE,
	E_CARD_SIMPLE_FIELD_MAILER,
	E_CARD_SIMPLE_FIELD_NAME_OR_ORG,
	E_CARD_SIMPLE_FIELD_CATEGORIES,
        E_CARD_SIMPLE_FIELD_FAMILY_NAME,
        E_CARD_SIMPLE_FIELD_GIVEN_NAME,
        E_CARD_SIMPLE_FIELD_ADDITIONAL_NAME,
        E_CARD_SIMPLE_FIELD_NAME_SUFFIX,
	E_CARD_SIMPLE_FIELD_WANTS_HTML,
	E_CARD_SIMPLE_FIELD_IS_LIST,
        E_CARD_SIMPLE_FIELD_LAST
};

typedef struct _ECardSimple ECardSimple;
typedef struct _ECardSimpleClass ECardSimpleClass;

struct _ECardSimple {
	GObject object;
	ECard *card;

	GList *temp_fields;

	ECardPhone *phone[E_CARD_SIMPLE_PHONE_ID_LAST];
	char *email[E_CARD_SIMPLE_EMAIL_ID_LAST];
	ECardAddrLabel *address[E_CARD_SIMPLE_ADDRESS_ID_LAST];
	ECardDeliveryAddress *delivery[E_CARD_SIMPLE_ADDRESS_ID_LAST];

	gboolean changed;
};

struct _ECardSimpleClass {
	GObjectClass parent_class;
};

typedef void (*ECardSimpleArbitraryCallback) (const ECardArbitrary *arbitrary, gpointer closure);
ECardSimple                *e_card_simple_new                    (ECard                        *card);
const char                 *e_card_simple_get_id                 (ECardSimple                  *simple);
void                        e_card_simple_set_id                 (ECardSimple                  *simple,
								  const gchar                  *character);
char                       *e_card_simple_get_vcard              (ECardSimple                  *simple);
char                       *e_card_simple_get_vcard_assume_utf8  (ECardSimple                  *simple);
ECardSimple                *e_card_simple_duplicate              (ECardSimple                  *simple);
char                       *e_card_simple_get                    (ECardSimple                  *simple,
								  ECardSimpleField              field);
const char                 *e_card_simple_get_const              (ECardSimple                  *simple,
								  ECardSimpleField              field);
void                        e_card_simple_set                    (ECardSimple                  *simple,
								  ECardSimpleField              field,
								  const char                   *data);
ECardSimpleType             e_card_simple_type                   (ECardSimple                  *simple,
								  ECardSimpleField              field);

const char                 *e_card_simple_get_ecard_field        (ECardSimple                  *simple,
								  ECardSimpleField              field);
const char                 *e_card_simple_get_name               (ECardSimple                  *simple,
								  ECardSimpleField              field);
const char                 *e_card_simple_get_short_name         (ECardSimple                  *simple,
								  ECardSimpleField              field);
gboolean                    e_card_simple_get_allow_newlines     (ECardSimple                  *simple,
								  ECardSimpleField              field);


/* Use these only if building lists of specific types.  It should be
 * easier to use the above if you consider a phone field to be the
 * same as any other field.
 */
const ECardPhone           *e_card_simple_get_phone              (ECardSimple                  *simple,
								  ECardSimplePhoneId            id);
const char                 *e_card_simple_get_email              (ECardSimple                  *simple,
								  ECardSimpleEmailId            id);
const ECardAddrLabel       *e_card_simple_get_address            (ECardSimple                  *simple,
								  ECardSimpleAddressId          id);
const ECardDeliveryAddress *e_card_simple_get_delivery_address   (ECardSimple                  *simple,
								  ECardSimpleAddressId          id);
void                        e_card_simple_set_phone              (ECardSimple                  *simple,
								  ECardSimplePhoneId            id,
								  const ECardPhone             *phone);
void                        e_card_simple_set_email              (ECardSimple                  *simple,
								  ECardSimpleEmailId            id,
								  const char                   *email);
void                        e_card_simple_set_address            (ECardSimple                  *simple,
								  ECardSimpleAddressId          id,
								  const ECardAddrLabel         *address);
void                        e_card_simple_set_delivery_address   (ECardSimple                  *simple,
								  ECardSimpleAddressId          id,
								  const ECardDeliveryAddress   *delivery);
void                        e_card_simple_arbitrary_foreach      (ECardSimple                  *simple,
								  ECardSimpleArbitraryCallback *callback,
								  gpointer                      closure);
const ECardArbitrary       *e_card_simple_get_arbitrary          (ECardSimple                  *simple,
								  const char                   *key);
/* Any of these except key can be NULL */	      
void                        e_card_simple_set_arbitrary          (ECardSimple                  *simple,
								  const char                   *key,
								  const char                   *type,
								  const char                   *value);
void                        e_card_simple_set_name               (ECardSimple                  *simple,
								  ECardName                    *name);
void                        e_card_simple_sync_card              (ECardSimple                  *simple);

/* These map between the individual list types and ECardSimpleField */
ECardSimpleField            e_card_simple_map_phone_to_field     (ECardSimplePhoneId            phone_id);
ECardSimpleField            e_card_simple_map_email_to_field     (ECardSimpleEmailId            email_id);
ECardSimpleField            e_card_simple_map_address_to_field   (ECardSimpleAddressId          address_id);

GType                       e_card_simple_get_type               (void);

#endif /* ! __E_CARD_SIMPLE_H__ */


