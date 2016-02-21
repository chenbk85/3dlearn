
```
#pragma once

typedef struct lua_State lua_State;
typedef int (*lua_CFunction) (lua_State *L);
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
typedef double lua_Number;
typedef ptrdiff_t lua_Integer;
typedef unsigned int lua_Unsigned;
typedef struct lua_Debug lua_Debug;  
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);

__declspec(dllexport) lua_State *(lua_newstate) (lua_Alloc f, void *ud);
__declspec(dllexport) void       (lua_close) (lua_State *L);
__declspec(dllexport) lua_State *(lua_newthread) (lua_State *L);
__declspec(dllexport) lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);
__declspec(dllexport) const lua_Number *(lua_version) (lua_State *L);
__declspec(dllexport) int   (lua_absindex) (lua_State *L, int idx);
__declspec(dllexport) int   (lua_gettop) (lua_State *L);
__declspec(dllexport) void  (lua_settop) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_pushvalue) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_remove) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_insert) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_replace) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_copy) (lua_State *L, int fromidx, int toidx);
__declspec(dllexport) int   (lua_checkstack) (lua_State *L, int sz);
__declspec(dllexport) void  (lua_xmove) (lua_State *from, lua_State *to, int n);
__declspec(dllexport) int             (lua_isnumber) (lua_State *L, int idx);
__declspec(dllexport) int             (lua_isstring) (lua_State *L, int idx);
__declspec(dllexport) int             (lua_iscfunction) (lua_State *L, int idx);
__declspec(dllexport) int             (lua_isuserdata) (lua_State *L, int idx);
__declspec(dllexport) int             (lua_type) (lua_State *L, int idx);
__declspec(dllexport) const char     *(lua_typename) (lua_State *L, int tp);
__declspec(dllexport) lua_Number      (lua_tonumberx) (lua_State *L, int idx, int *isnum);
__declspec(dllexport) lua_Integer     (lua_tointegerx) (lua_State *L, int idx, int *isnum);
__declspec(dllexport) lua_Unsigned    (lua_tounsignedx) (lua_State *L, int idx, int *isnum);
__declspec(dllexport) int             (lua_toboolean) (lua_State *L, int idx);
__declspec(dllexport) const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);
__declspec(dllexport) size_t          (lua_rawlen) (lua_State *L, int idx);
__declspec(dllexport) lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);
__declspec(dllexport) void	       *(lua_touserdata) (lua_State *L, int idx);
__declspec(dllexport) lua_State      *(lua_tothread) (lua_State *L, int idx);
__declspec(dllexport) const void     *(lua_topointer) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_arith) (lua_State *L, int op);
__declspec(dllexport) int   (lua_rawequal) (lua_State *L, int idx1, int idx2);
__declspec(dllexport) int   (lua_compare) (lua_State *L, int idx1, int idx2, int op);
__declspec(dllexport) void        (lua_pushnil) (lua_State *L);
__declspec(dllexport) void        (lua_pushnumber) (lua_State *L, lua_Number n);
__declspec(dllexport) void        (lua_pushinteger) (lua_State *L, lua_Integer n);
__declspec(dllexport) void        (lua_pushunsigned) (lua_State *L, lua_Unsigned n);
__declspec(dllexport) const char *(lua_pushlstring) (lua_State *L, const char *s, size_t l);
__declspec(dllexport) const char *(lua_pushstring) (lua_State *L, const char *s);
__declspec(dllexport) const char *(lua_pushvfstring) (lua_State *L, const char *fmt,
                                                      va_list argp);
__declspec(dllexport) const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);
__declspec(dllexport) void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
__declspec(dllexport) void  (lua_pushboolean) (lua_State *L, int b);
__declspec(dllexport) void  (lua_pushlightuserdata) (lua_State *L, void *p);
__declspec(dllexport) int   (lua_pushthread) (lua_State *L);
__declspec(dllexport) void  (lua_getglobal) (lua_State *L, const char *var);
__declspec(dllexport) void  (lua_gettable) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_getfield) (lua_State *L, int idx, const char *k);
__declspec(dllexport) void  (lua_rawget) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_rawgeti) (lua_State *L, int idx, int n);
__declspec(dllexport) void  (lua_rawgetp) (lua_State *L, int idx, const void *p);
__declspec(dllexport) void  (lua_createtable) (lua_State *L, int narr, int nrec);
__declspec(dllexport) void *(lua_newuserdata) (lua_State *L, size_t sz);
__declspec(dllexport) int   (lua_getmetatable) (lua_State *L, int objindex);
__declspec(dllexport) void  (lua_getuservalue) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_setglobal) (lua_State *L, const char *var);
__declspec(dllexport) void  (lua_settable) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_setfield) (lua_State *L, int idx, const char *k);
__declspec(dllexport) void  (lua_rawset) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_rawseti) (lua_State *L, int idx, int n);
__declspec(dllexport) void  (lua_rawsetp) (lua_State *L, int idx, const void *p);
__declspec(dllexport) int   (lua_setmetatable) (lua_State *L, int objindex);
__declspec(dllexport) void  (lua_setuservalue) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_callk) (lua_State *L, int nargs, int nresults, int ctx,
                           lua_CFunction k);
__declspec(dllexport) int   (lua_getctx) (lua_State *L, int *ctx);
__declspec(dllexport) int   (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc,
                            int ctx, lua_CFunction k);
__declspec(dllexport) int   (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                                        const char *chunkname,
                                        const char *mode);
__declspec(dllexport) int (lua_dump) (lua_State *L, lua_Writer writer, void *data);
__declspec(dllexport) int  (lua_yieldk) (lua_State *L, int nresults, int ctx,
                           lua_CFunction k);
__declspec(dllexport) int  (lua_resume) (lua_State *L, lua_State *from, int narg);
__declspec(dllexport) int  (lua_status) (lua_State *L);
__declspec(dllexport) int (lua_gc) (lua_State *L, int what, int data);
__declspec(dllexport) int   (lua_error) (lua_State *L);
__declspec(dllexport) int   (lua_next) (lua_State *L, int idx);
__declspec(dllexport) void  (lua_concat) (lua_State *L, int n);
__declspec(dllexport) void  (lua_len)    (lua_State *L, int idx);
__declspec(dllexport) lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
__declspec(dllexport) void      (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);
__declspec(dllexport) int (lua_getstack) (lua_State *L, int level, lua_Debug *ar);
__declspec(dllexport) int (lua_getinfo) (lua_State *L, const char *what, lua_Debug *ar);
__declspec(dllexport) const char *(lua_getlocal) (lua_State *L, const lua_Debug *ar, int n);
__declspec(dllexport) const char *(lua_setlocal) (lua_State *L, const lua_Debug *ar, int n);
__declspec(dllexport) const char *(lua_getupvalue) (lua_State *L, int funcindex, int n);
__declspec(dllexport) const char *(lua_setupvalue) (lua_State *L, int funcindex, int n);
__declspec(dllexport) void *(lua_upvalueid) (lua_State *L, int fidx, int n);
__declspec(dllexport) void  (lua_upvaluejoin) (lua_State *L, int fidx1, int n1,
                                               int fidx2, int n2);
__declspec(dllexport) int (lua_sethook) (lua_State *L, lua_Hook func, int mask, int count);
__declspec(dllexport) lua_Hook (lua_gethook) (lua_State *L);
__declspec(dllexport) int (lua_gethookmask) (lua_State *L);
__declspec(dllexport) int (lua_gethookcount) (lua_State *L);

struct lua_Debug {
  int event;
  const char *name;	
  const char *namewhat;	
  const char *what;	
  const char *source;	
  int currentline;	
  int linedefined;	
  int lastlinedefined;	
  unsigned char nups;	
  unsigned char nparams;
  char isvararg;        
  char istailcall;	
  char short_src[60]; 
  
  struct CallInfo *i_ci;  
};

typedef unsigned int lu_int32;
typedef size_t lu_mem;
typedef ptrdiff_t l_mem;
typedef unsigned char lu_byte;
typedef union { double u; void *s; long l; } L_Umaxalign;
typedef double l_uacNumber;
typedef lu_int32 Instruction;

typedef union GCObject GCObject;

typedef struct GCheader {
  GCObject *next; 
  lu_byte tt;
  lu_byte marked;
} GCheader;

typedef union Value Value;
typedef struct lua_TValue TValue;

union Value {
  GCObject *gc;    
  void *p;         
  int b;           
  lua_CFunction f; 
           
};

struct lua_TValue {
  union { struct { Value v__; int tt__; } i; double d__; } u;
};

typedef TValue *StkId; 
 
typedef union TString {
  L_Umaxalign dummy;  
  struct {
    GCObject *next; lu_byte tt; lu_byte marked;
    lu_byte reserved;
    unsigned int hash;
    size_t len;  
  } tsv;
} TString;

typedef union Udata {
  L_Umaxalign dummy;  
  struct {
    GCObject *next; lu_byte tt; lu_byte marked;
    struct Table *metatable;
    struct Table *env;
    size_t len;  
  } uv;
} Udata;

typedef struct Upvaldesc {
  TString *name;  
  lu_byte instack;  
  lu_byte idx;  
} Upvaldesc;

typedef struct LocVar {
  TString *varname;
  int startpc;  
  int endpc;    
} LocVar;

typedef struct Proto {
  GCObject *next; lu_byte tt; lu_byte marked;
  TValue *k;  
  Instruction *code;
  struct Proto **p;  
  int *lineinfo;  
  LocVar *locvars;  
  Upvaldesc *upvalues;  
  union Closure *cache;  
  TString  *source;  
  int sizeupvalues;  
  int sizek;  
  int sizecode;
  int sizelineinfo;
  int sizep;  
  int sizelocvars;
  int linedefined;
  int lastlinedefined;
  GCObject *gclist;
  lu_byte numparams;  
  lu_byte is_vararg;
  lu_byte maxstacksize;  
} Proto;

typedef struct UpVal {
  GCObject *next; lu_byte tt; lu_byte marked;
  TValue *v;  
  union {
    TValue value;  
    struct {  
      struct UpVal *prev;
      struct UpVal *next;
    } l;
  } u;
} UpVal;

typedef struct CClosure {
  GCObject *next; 
  lu_byte tt;
  lu_byte marked; 
  lu_byte isC; 
  lu_byte nupvalues;
  GCObject *gclist;
  lua_CFunction f;
  TValue upvalue[1];  
} CClosure;

typedef struct LClosure {
  GCObject *next; 
  lu_byte tt;
  lu_byte marked; 
  lu_byte isC; 
  lu_byte nupvalues; 
  GCObject *gclist;
  struct Proto *p;
  UpVal *upvals[1];  
} LClosure;

typedef union Closure {
  CClosure c;
  LClosure l;
} Closure;

typedef union TKey {
  struct {
    union { struct { Value v__; int tt__; } i; double d__; } u;
    struct Node *next;  
  } nk;
  TValue tvk;
} TKey;

typedef struct Node {
  TValue i_val;
  TKey i_key;
} Node;

typedef struct Table {
  GCObject *next; 
  lu_byte tt;
  lu_byte marked;
  lu_byte flags;  
  lu_byte lsizenode;  
  struct Table *metatable;
  TValue *array;  
  Node *node;
  Node *lastfree;  
  GCObject *gclist;
  int sizearray;  
} Table;

extern const TValue luaO_nilobject_;
extern int luaO_int2fb (unsigned int x);
extern int luaO_fb2int (int x);
extern int luaO_ceillog2 (unsigned int x);
extern lua_Number luaO_arith (int op, lua_Number v1, lua_Number v2);
extern int luaO_str2d (const char *s, size_t len, lua_Number *result);
extern int luaO_hexavalue (int c);
extern const char *luaO_pushvfstring (lua_State *L, const char *fmt,
                                                       va_list argp);
extern const char *luaO_pushfstring (lua_State *L, const char *fmt, ...);
extern void luaO_chunkid (char *out, const char *source, size_t len);

typedef enum {
  TM_INDEX,
  TM_NEWINDEX,
  TM_GC,
  TM_MODE,
  TM_LEN,
  TM_EQ,  
  TM_ADD,
  TM_SUB,
  TM_MUL,
  TM_DIV,
  TM_MOD,
  TM_POW,
  TM_UNM,
  TM_LT,
  TM_LE,
  TM_CONCAT,
  TM_CALL,
  TM_N		
} TMS;

extern const char *const luaT_typenames_[((9+1)+2)];
extern const TValue *luaT_gettm (Table *events, TMS event, TString *ename);
extern const TValue *luaT_gettmbyobj (lua_State *L, const TValue *o,
                                                       TMS event);
extern void luaT_init (lua_State *L);
extern void __declspec(noreturn) luaM_toobig (lua_State *L);
extern void *luaM_realloc_ (lua_State *L, void *block, size_t oldsize,
                                                          size_t size);
extern void *luaM_growaux_ (lua_State *L, void *block, int *size,
                               size_t size_elem, int limit,
                               const char *what);
							   
typedef struct Zio ZIO;
typedef struct Mbuffer {
  char *buffer;
  size_t n;
  size_t buffsize;
} Mbuffer;

extern char *luaZ_openspace (lua_State *L, Mbuffer *buff, size_t n);
extern void luaZ_init (lua_State *L, ZIO *z, lua_Reader reader,
                                        void *data);
extern size_t luaZ_read (ZIO* z, void* b, size_t n);	
struct Zio {
  size_t n;			
  const char *p;		
  lua_Reader reader;		
  void* data;			
  lua_State *L;			
};

extern int luaZ_fill (ZIO *z);
struct lua_longjmp;  

typedef struct stringtable {
  GCObject **hash;
  lu_int32 nuse;  
  int size;
} stringtable;

typedef struct CallInfo {
  StkId func;  
  StkId	top;  
  struct CallInfo *previous, *next;  
  short nresults;  
  lu_byte callstatus;
  union {
    struct {  
      StkId base;  
      const Instruction *savedpc;
    } l;
    struct {  
      int ctx;  
      lua_CFunction k;  
      ptrdiff_t old_errfunc;
      ptrdiff_t extra;
      lu_byte old_allowhook;
      lu_byte status;
    } c;
  } u;
} CallInfo;

typedef struct global_State {
  lua_Alloc frealloc;  
  void *ud;         
  lu_mem totalbytes;  
  l_mem GCdebt;  
  lu_mem lastmajormem;  
  stringtable strt;  
  TValue l_registry;
  lu_byte currentwhite;
  lu_byte gcstate;  
  lu_byte gckind;  
  lu_byte gcrunning;  
  int sweepstrgc;  
  GCObject *allgc;  
  GCObject *finobj;  
  GCObject **sweepgc;  
  GCObject *gray;  
  GCObject *grayagain;  
  GCObject *weak;  
  GCObject *ephemeron;  
  GCObject *allweak;  
  GCObject *tobefnz;  
  UpVal uvhead;  
  Mbuffer buff;  
  int gcpause;  
  int gcmajorinc;  
  int gcstepmul;  
  lua_CFunction panic;  
  struct lua_State *mainthread;
  const lua_Number *version;  
  TString *memerrmsg;  
  TString *tmname[TM_N];  
  struct Table *mt[9];  
} global_State;

struct lua_State {
  GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte status;
  StkId top;  
  global_State *l_G;
  CallInfo *ci;  
  const Instruction *oldpc;  
  StkId stack_last;  
  StkId stack;  
  int stacksize;
  unsigned short nny;  
  unsigned short nCcalls;  
  lu_byte hookmask;
  lu_byte allowhook;
  int basehookcount;
  int hookcount;
  lua_Hook hook;
  GCObject *openupval;  
  GCObject *gclist;
  struct lua_longjmp *errorJmp;  
  ptrdiff_t errfunc;  
  CallInfo base_ci;  
};

union GCObject {
  GCheader gch;  
  union TString ts;
  union Udata u;
  union Closure cl;
  struct Table h;
  struct Proto p;
  struct UpVal uv;
  struct lua_State th;  
};

extern void luaE_setdebt (global_State *g, l_mem debt);
extern void luaE_freethread (lua_State *L, lua_State *L1);
extern CallInfo *luaE_extendCI (lua_State *L);
extern void luaE_freeCI (lua_State *L);
extern void __declspec(noreturn) luaG_typeerror (lua_State *L, const TValue *o,
                                                const char *opname);
extern void __declspec(noreturn) luaG_concaterror (lua_State *L, StkId p1, StkId p2);
extern void __declspec(noreturn) luaG_aritherror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
extern void __declspec(noreturn) luaG_ordererror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
extern void __declspec(noreturn) luaG_runerror (lua_State *L, const char *fmt, ...);
extern void __declspec(noreturn) luaG_errormsg (lua_State *L);
typedef void (*Pfunc) (lua_State *L, void *ud);
extern int luaD_protectedparser (lua_State *L, ZIO *z, const char *name,
                                                  const char *mode);
extern void luaD_hook (lua_State *L, int event, int line);
extern int luaD_precall (lua_State *L, StkId func, int nresults);
extern void luaD_call (lua_State *L, StkId func, int nResults,
                                        int allowyield);
extern int luaD_pcall (lua_State *L, Pfunc func, void *u,
                                        ptrdiff_t oldtop, ptrdiff_t ef);
extern int luaD_poscall (lua_State *L, StkId firstResult);
extern void luaD_reallocstack (lua_State *L, int newsize);
extern void luaD_growstack (lua_State *L, int n);
extern void luaD_shrinkstack (lua_State *L);
extern void __declspec(noreturn) luaD_throw (lua_State *L, int errcode);
extern int luaD_rawrunprotected (lua_State *L, Pfunc f, void *ud);
extern Proto *luaF_newproto (lua_State *L);
extern Closure *luaF_newCclosure (lua_State *L, int nelems);
extern Closure *luaF_newLclosure (lua_State *L, Proto *p);
extern UpVal *luaF_newupval (lua_State *L);
extern UpVal *luaF_findupval (lua_State *L, StkId level);
extern void luaF_close (lua_State *L, StkId level);
extern void luaF_freeproto (lua_State *L, Proto *f);
extern void luaF_freeclosure (lua_State *L, Closure *c);
extern void luaF_freeupval (lua_State *L, UpVal *uv);
extern const char *luaF_getlocalname (const Proto *func, int local_number,
                                         int pc);
extern void luaC_freeallobjects (lua_State *L);
extern void luaC_step (lua_State *L);
extern void luaC_forcestep (lua_State *L);
extern void luaC_runtilstate (lua_State *L, int statesmask);
extern void luaC_fullgc (lua_State *L, int isemergency);
extern GCObject *luaC_newobj (lua_State *L, int tt, size_t sz,
                                 GCObject **list, int offset);
extern void luaC_barrier_ (lua_State *L, GCObject *o, GCObject *v);
extern void luaC_barrierback_ (lua_State *L, GCObject *o);
extern void luaC_barrierproto_ (lua_State *L, Proto *p, Closure *c);
extern void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt);
extern void luaC_checkupvalcolor (global_State *g, UpVal *uv);
extern void luaC_changemode (lua_State *L, int mode);
extern void luaS_resize (lua_State *L, int newsize);
extern Udata *luaS_newudata (lua_State *L, size_t s, Table *e);
extern TString *luaS_newlstr (lua_State *L, const char *str, size_t l);
extern TString *luaS_new (lua_State *L, const char *str);
extern const TValue *luaH_getint (Table *t, int key);
extern void luaH_setint (lua_State *L, Table *t, int key, TValue *value);
extern const TValue *luaH_getstr (Table *t, TString *key);
extern const TValue *luaH_get (Table *t, const TValue *key);
extern TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key);
extern TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
extern Table *luaH_new (lua_State *L);
extern void luaH_resize (lua_State *L, Table *t, int nasize, int nhsize);
extern void luaH_resizearray (lua_State *L, Table *t, int nasize);
extern void luaH_free (lua_State *L, Table *t);
extern int luaH_next (lua_State *L, Table *t, StkId key);
extern int luaH_getn (Table *t);
extern Proto* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name);
extern void luaU_header (lu_byte* h);
extern int luaU_dump (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip);
extern int luaV_equalobj_ (lua_State *L, const TValue *t1, const TValue *t2);
extern int luaV_lessthan (lua_State *L, const TValue *l, const TValue *r);
extern int luaV_lessequal (lua_State *L, const TValue *l, const TValue *r);
extern const TValue *luaV_tonumber (const TValue *obj, TValue *n);
extern int luaV_tostring (lua_State *L, StkId obj);
extern void luaV_gettable (lua_State *L, const TValue *t, TValue *key,
                                            StkId val);
extern void luaV_settable (lua_State *L, const TValue *t, TValue *key,
                                            StkId val);
extern void luaV_finishOp (lua_State *L);
extern void luaV_execute (lua_State *L);
extern void luaV_concat (lua_State *L, int total);
extern void luaV_arith (lua_State *L, StkId ra, const TValue *rb,
                           const TValue *rc, TMS op);
extern void luaV_objlen (lua_State *L, StkId ra, const TValue *rb);
const char lua_ident[] =
  "$LuaVersion: " "Lua " "5" "." "2" "." "0" "  Copyright (C) 1994-2011 Lua.org, PUC-Rio" " $"
  "$LuaAuthors: " "R. Ierusalimschy, L. H. de Figueiredo, W. Celes" " $";

```