/*  
 *  $Id$
 *
 *                              
 *                    L O S  A L A M O S
 *              Los Alamos National Laboratory
 *               Los Alamos, New Mexico 87545
 *                                  
 *  Copyright, 1986, The Regents of the University of California.
 *                                  
 *           
 *	Author Jeffrey O. Hill
 *	johill@lanl.gov
 *	505 665 1831
 */

#ifndef netIOh  
#define netIOh

#include "nciu.h"

// does the local compiler support placement delete
#if defined (_MSC_VER) 
#   if _MSC_VER >= 1200
#       define NETIO_PLACEMENT_DELETE
#   endif
#elif defined ( __HP_aCC )
#   if _HP_aCC > 033300
#       define NETIO_PLACEMENT_DELETE
#   endif
#else
#   define NETIO_PLACEMENT_DELETE
#endif

class baseNMIU : public tsDLNode < baseNMIU >, // X aCC 655
        public chronIntIdRes < baseNMIU > {
public:
    virtual ~baseNMIU (); 
    virtual void destroy ( class cacRecycle & ) = 0; // only called by cac
    virtual void completion () = 0;
    virtual void exception ( int status, 
        const char * pContext ) = 0;
    virtual void exception ( int status, 
        const char * pContext, unsigned type, 
        arrayElementCount count ) = 0;
    virtual void completion ( unsigned type, 
        arrayElementCount count, const void * pData ) = 0;
    virtual class netSubscription * isSubscription () = 0;
    virtual void show ( unsigned level ) const = 0;
//
// not fond of the vf overhead to fetch this
//
    virtual nciu & channel () const = 0;
};

class netSubscription : public baseNMIU  {
public:
    static netSubscription * factory ( 
        tsFreeList < class netSubscription, 1024, epicsMutexNOOP > &, 
        nciu & chan, unsigned type, arrayElementCount count, 
        unsigned mask, cacStateNotify &notify );
    void show ( unsigned level ) const;
    arrayElementCount getCount () const;
    unsigned getType () const;
    unsigned getMask () const;
private:
    const arrayElementCount count;
    nciu & chan;
    cacStateNotify & notify;
    const unsigned type;
    const unsigned mask;
    netSubscription ( nciu & chan, unsigned type, arrayElementCount count, 
        unsigned mask, cacStateNotify &notify );
    class netSubscription * isSubscription ();
    void * operator new ( size_t );
    void operator delete ( void * );
    void * operator new ( size_t, 
        tsFreeList < class netSubscription, 1024, epicsMutexNOOP > & );
#   if defined ( NETIO_PLACEMENT_DELETE )
    void operator delete ( void *, 
        tsFreeList < class netSubscription, 1024, epicsMutexNOOP > & );
#   endif
    void destroy ( class cacRecycle & );
    void completion ();
    void exception ( int status, 
        const char *pContext );
    void completion ( unsigned type, 
        arrayElementCount count, const void *pData );
    void exception ( int status, 
        const char *pContext, unsigned type, 
        arrayElementCount count );
    nciu & channel () const;
    netSubscription ( const netSubscription & );
    netSubscription & operator = ( const netSubscription & );
    ~netSubscription ();
};

class netReadNotifyIO : public baseNMIU {
public:
    static netReadNotifyIO * factory ( 
        tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > &, 
        nciu &chan, cacReadNotify &notify );
    void show ( unsigned level ) const;
private:
    cacReadNotify & notify;
    nciu & chan;
    netReadNotifyIO ( nciu & chan, cacReadNotify & notify );
    void * operator new ( size_t );
    void operator delete ( void * );
    void * operator new ( size_t, 
        tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > & );
#   if defined ( NETIO_PLACEMENT_DELETE )
    void operator delete ( void *, 
        tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > & );
#   endif
    void destroy ( class cacRecycle & );
    void completion ();
    void exception ( int status, const char *pContext );
    void completion ( unsigned type, 
        arrayElementCount count, const void *pData );
    void exception ( int status, const char *pContext, 
        unsigned type, arrayElementCount count );
    nciu & channel () const;
    ~netReadNotifyIO ();
    class netSubscription * isSubscription ();
    netReadNotifyIO ( const netReadNotifyIO & );
    netReadNotifyIO & operator = ( const netReadNotifyIO & );
};

class netWriteNotifyIO : public baseNMIU {
public:
    static netWriteNotifyIO * factory ( 
        tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > &, 
        nciu &chan, cacWriteNotify &notify );
    void show ( unsigned level ) const;
private:
    cacWriteNotify & notify;
    nciu & chan;
    netWriteNotifyIO ( nciu &chan, cacWriteNotify &notify );
    void * operator new ( size_t );
    void operator delete ( void * );
    void * operator new ( size_t, 
        tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > & );
#   if defined ( NETIO_PLACEMENT_DELETE )
    void operator delete ( void *,
        tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > & );
#   endif
    class netSubscription * isSubscription ();
    void destroy ( class cacRecycle & );
    void completion ();
    void exception ( int status, const char *pContext );
    void completion ( unsigned type, 
        arrayElementCount count, const void *pData );
    void exception ( int status, const char *pContext, 
        unsigned type, arrayElementCount count );
    nciu & channel () const;
    netWriteNotifyIO ( const netWriteNotifyIO & );
    netWriteNotifyIO & operator = ( const netWriteNotifyIO & );
    ~netWriteNotifyIO ();
};

inline void * netSubscription::operator new ( size_t size, 
    tsFreeList < class netSubscription, 1024, epicsMutexNOOP > &freeList )
{
    return freeList.allocate ( size );
}

#if defined ( NETIO_PLACEMENT_DELETE )
    inline void netSubscription::operator delete ( void *pCadaver, 
        tsFreeList < class netSubscription, 1024, epicsMutexNOOP > &freeList )
    {
        freeList.release ( pCadaver, sizeof ( netSubscription ) );
    }
#endif

inline void * netSubscription::operator new ( size_t sizeIn )
{
    return ::operator new ( sizeIn );
}

inline void netSubscription::operator delete ( void * p )
{
    ::operator delete ( p );
}

inline netSubscription * netSubscription::factory ( 
    tsFreeList < class netSubscription, 1024, epicsMutexNOOP > &freeList, 
    nciu &chan, unsigned type, arrayElementCount count, 
    unsigned mask, cacStateNotify &notify )
{
    return new ( freeList ) netSubscription ( chan, type, 
                                count, mask, notify );
}

inline arrayElementCount netSubscription::getCount () const // X aCC 361
{
    arrayElementCount nativeCount = this->chan.nativeElementCount ();
    if ( this->count == 0u || this->count > nativeCount ) {
        return nativeCount;
    }
    else {
        return this->count;
    }
}

inline unsigned netSubscription::getType () const
{
    return this->type;
}

inline unsigned netSubscription::getMask () const
{
    return this->mask;
}

inline netReadNotifyIO * netReadNotifyIO::factory ( 
    tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > &freeList, 
    nciu &chan, cacReadNotify &notify )
{
    return new ( freeList ) netReadNotifyIO ( chan, notify );
}

inline void * netReadNotifyIO::operator new ( size_t size, 
    tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > &freeList )
{
    return freeList.allocate ( size );
}

#if defined ( NETIO_PLACEMENT_DELETE )
    inline void netReadNotifyIO::operator delete ( void *pCadaver, 
        tsFreeList < class netReadNotifyIO, 1024, epicsMutexNOOP > &freeList )
    {
        freeList.release ( pCadaver, sizeof ( netWriteNotifyIO ) );
    }
#endif

inline void * netReadNotifyIO::operator new ( size_t sizeIn )
{
    return ::operator new ( sizeIn );
}

inline void netReadNotifyIO::operator delete ( void * p )
{
    ::operator delete ( p );
}

inline netWriteNotifyIO * netWriteNotifyIO::factory ( 
    tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > &freeList, 
    nciu &chan, cacWriteNotify &notify )
{
    return new ( freeList ) netWriteNotifyIO ( chan, notify );
}

inline void * netWriteNotifyIO::operator new ( size_t size, 
        tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > &freeList )
{ 
    return freeList.allocate ( size );
}

#if defined ( NETIO_PLACEMENT_DELETE )
    inline void netWriteNotifyIO::operator delete ( void *pCadaver, 
        tsFreeList < class netWriteNotifyIO, 1024, epicsMutexNOOP > &freeList )
    {
        freeList.release ( pCadaver, sizeof ( netWriteNotifyIO ) );
    }
#endif

inline void * netWriteNotifyIO::operator new ( size_t sizeIn )
{
    return ::operator new ( sizeIn );
}

inline void netWriteNotifyIO::operator delete ( void * p )
{
    ::operator delete ( p );
}

#endif // ifdef netIOh
