
```

static TValue *index2addr (lua_State *L, int idx) {
  CallInfo *ci = L->ci;
  if (idx > 0) {
    TValue *o = ci->func + idx;
    ((void)0);
    if (o >= L->top) return ((TValue *)((&luaO_nilobject_)));
    else return o;
  }
  else if (idx > (-1000000 - 1000)) {
    ((void)0);
    return L->top + idx;
  }
  else if (idx == (-1000000 - 1000))
    return &(L->l_G)->l_registry;
  else {  
    idx = (-1000000 - 1000) - idx;
    ((void)0);
    if (((((ci->func))->u.i.tt__) == (0x7FF7A500 | ((6 | (1 << 4))))))  
      return ((TValue *)((&luaO_nilobject_)));  
    else {
      CClosure *func = (&((ci->func)->u.i.v__).gc->cl.c);
      return (idx <= func->nupvalues) ? &func->upvalue[idx-1] : ((TValue *)((&luaO_nilobject_)));
    }
  }
}
static void growstack (lua_State *L, void *ud) {
  int size = *(int *)ud;
  luaD_growstack(L, size);
}

__declspec(dllexport) int lua_checkstack (lua_State *L, int size) {
  int res;
  CallInfo *ci = L->ci;
  ((void) 0);
  if (L->stack_last - L->top > size)  
    res = 1;  
  else {  
    int inuse = ((int)((L->top - L->stack))) + 5;
    if (inuse > 1000000 - size)  
      res = 0;  
    else  
      res = (luaD_rawrunprotected(L, &growstack, &size) == 0);
  }
  if (res && ci->top < L->top + size)
    ci->top = L->top + size;  
  ((void) 0);
  return res;
}

__declspec(dllexport) void lua_xmove (lua_State *from, lua_State *to, int n) {
  int i;
  if (from == to) return;
  ((void) 0);
  ((void)0);
  ((void)0);
  ((void)0);
  from->top -= n;
  for (i = 0; i < n; i++) {
    { const TValue *o2_=(from->top + i); TValue *o1_=(to->top++); o1_->u = o2_->u; ((void)0); };
  }
  ((void) 0);
}

__declspec(dllexport) lua_CFunction lua_atpanic (lua_State *L, lua_CFunction panicf) {
  lua_CFunction old;
  ((void) 0);
  old = (L->l_G)->panic;
  (L->l_G)->panic = panicf;
  ((void) 0);
  return old;
}

__declspec(dllexport) const lua_Number *lua_version (lua_State *L) {
  static const lua_Number version = 502;
  if (L == ((void *)0)) return &version;
  else return (L->l_G)->version;
}

__declspec(dllexport) int lua_absindex (lua_State *L, int idx) {
  return (idx > 0 || idx <= (-1000000 - 1000))
         ? idx
         : ((int)((L->top - L->ci->func + idx)));
}

__declspec(dllexport) int lua_gettop (lua_State *L) {
  return ((int)((L->top - (L->ci->func + 1))));
}

__declspec(dllexport) void lua_settop (lua_State *L, int idx) {
  StkId func = L->ci->func;
  ((void) 0);
  if (idx >= 0) {
    ((void)0);
    while (L->top < (func + 1) + idx)
      (((L->top++)->u.i.tt__) = (0x7FF7A500 | (0)));
    L->top = (func + 1) + idx;
  }
  else {
    ((void)0);
    L->top += idx+1;  
  }
  ((void) 0);
}

__declspec(dllexport) void lua_remove (lua_State *L, int idx) {
  StkId p;
  ((void) 0);
  p = index2addr(L, idx);
  ((void)0);
  while (++p < L->top) { const TValue *o2_=(p); TValue *o1_=(p-1); o1_->u = o2_->u; ((void)0); };
  L->top--;
  ((void) 0);
}

__declspec(dllexport) void lua_insert (lua_State *L, int idx) {
  StkId p;
  StkId q;
  ((void) 0);
  p = index2addr(L, idx);
  ((void)0);
  for (q = L->top; q>p; q--) { const TValue *o2_=(q-1); TValue *o1_=(q); o1_->u = o2_->u; ((void)0); };
  { const TValue *o2_=(L->top); TValue *o1_=(p); o1_->u = o2_->u; ((void)0); };
  ((void) 0);
}

static void moveto (lua_State *L, TValue *fr, int idx) {
  TValue *to = index2addr(L, idx);
  ((void)0);
  { const TValue *o2_=(fr); TValue *o1_=(to); o1_->u = o2_->u; ((void)0); };
  if (idx < (-1000000 - 1000))  
    { if ((((((((fr)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((fr)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((fr)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)(((&((L->ci->func)->u.i.v__).gc->cl.c))))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)(((&((L->ci->func)->u.i.v__).gc->cl.c))))),(((fr)->u.i.v__).gc)); };
  
}

__declspec(dllexport) void lua_replace (lua_State *L, int idx) {
  ((void) 0);
  ((void)0);
  moveto(L, L->top - 1, idx);
  L->top--;
  ((void) 0);
}

__declspec(dllexport) void lua_copy (lua_State *L, int fromidx, int toidx) {
  TValue *fr;
  ((void) 0);
  fr = index2addr(L, fromidx);
  ((void)0);
  moveto(L, fr, toidx);
  ((void) 0);
}

__declspec(dllexport) void lua_pushvalue (lua_State *L, int idx) {
  ((void) 0);
  { const TValue *o2_=(index2addr(L, idx)); TValue *o1_=(L->top); o1_->u = o2_->u; ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) int lua_type (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  return (((o) != (&luaO_nilobject_)) ? ((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff) & 0x0F) : (-1));
}
__declspec(dllexport) const char *lua_typename (lua_State *L, int t) {
  ((void)(L));
  return luaT_typenames_[(t) + 1];
}
__declspec(dllexport) int lua_iscfunction (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  return (((((o))->u.i.tt__) == (0x7FF7A500 | ((6 | (1 << 4))))) || (((((o))->u.i.tt__) == (0x7FF7A500 | ((((6 | (2 << 4))) | (1 << 6)))))));
}
__declspec(dllexport) int lua_isnumber (lua_State *L, int idx) {
  TValue n;
  const TValue *o = index2addr(L, idx);
  return (((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) || (((o) = luaV_tonumber(o,&n)) != ((void *)0)));
}
__declspec(dllexport) int lua_isstring (lua_State *L, int idx) {
  int t = lua_type(L, idx);
  return (t == 4 || t == 3);
}
__declspec(dllexport) int lua_isuserdata (lua_State *L, int idx) {
  const TValue *o = index2addr(L, idx);
  return (((((o))->u.i.tt__) == (0x7FF7A500 | (((7) | (1 << 6))))) || ((((o))->u.i.tt__) == (0x7FF7A500 | (2))));
}
__declspec(dllexport) int lua_rawequal (lua_State *L, int index1, int index2) {
  StkId o1 = index2addr(L, index1);
  StkId o2 = index2addr(L, index2);
  return (((o1) != (&luaO_nilobject_)) && ((o2) != (&luaO_nilobject_))) ? ((((((o1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? ((((o2)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) : (((o1)->u.i.tt__) == ((o2)->u.i.tt__))) && luaV_equalobj_(((void *)0),o1,o2)) : 0;
}
__declspec(dllexport) void  lua_arith (lua_State *L, int op) {
  StkId o1;  
  StkId o2;  
  ((void) 0);
  if (op != 6) 
    ((void)0);
  else {  
    ((void)0);
    { const TValue *o2_=(L->top - 1); TValue *o1_=(L->top); o1_->u = o2_->u; ((void)0); };
    L->top++;
  }
  o1 = L->top - 2;
  o2 = L->top - 1;
  if (((((o1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) && ((((o2)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500)) {
    (((o1)->u.d__)=(luaO_arith(op, (((o1)->u.d__)), (((o2)->u.d__)))));
  }
  else
    luaV_arith(L, o1, o1, o2, ((TMS)(op - 0 + TM_ADD)));
  L->top--;
  ((void) 0);
}
__declspec(dllexport) int lua_compare (lua_State *L, int index1, int index2, int op) {
  StkId o1, o2;
  int i = 0;
  ((void) 0);  
  o1 = index2addr(L, index1);
  o2 = index2addr(L, index2);
  if (((o1) != (&luaO_nilobject_)) && ((o2) != (&luaO_nilobject_))) {
    switch (op) {
      case 0: i = ((((((o1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? ((((o2)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) : (((o1)->u.i.tt__) == ((o2)->u.i.tt__))) && luaV_equalobj_(L, o1, o2)); break;
      case 1: i = luaV_lessthan(L, o1, o2); break;
      case 2: i = luaV_lessequal(L, o1, o2); break;
      default: ((void)0);
    }
  }
  ((void) 0);
  return i;
}
__declspec(dllexport) lua_Number lua_tonumberx (lua_State *L, int idx, int *isnum) {
  TValue n;
  const TValue *o = index2addr(L, idx);
  if ((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) || (((o) = luaV_tonumber(o,&n)) != ((void *)0)))) {
    if (isnum) *isnum = 1;
    return (((o)->u.d__));
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}
__declspec(dllexport) lua_Integer lua_tointegerx (lua_State *L, int idx, int *isnum) {
  TValue n;
  const TValue *o = index2addr(L, idx);
  if ((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) || (((o) = luaV_tonumber(o,&n)) != ((void *)0)))) {
    lua_Integer res;
    lua_Number num = (((o)->u.d__));
    __asm {__asm fld num __asm fistp res};
    if (isnum) *isnum = 1;
    return res;
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}
__declspec(dllexport) lua_Unsigned lua_tounsignedx (lua_State *L, int idx, int *isnum) {
  TValue n;
  const TValue *o = index2addr(L, idx);
  if ((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) || (((o) = luaV_tonumber(o,&n)) != ((void *)0)))) {
    lua_Unsigned res;
    lua_Number num = (((o)->u.d__));
    {__int64 l; __asm {__asm fld num __asm fistp l} res = (unsigned int)l;};
    if (isnum) *isnum = 1;
    return res;
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}
__declspec(dllexport) int lua_toboolean (lua_State *L, int idx) {
  const TValue *o = index2addr(L, idx);
  return !(((((o))->u.i.tt__) == (0x7FF7A500 | (0))) || (((((o))->u.i.tt__) == (0x7FF7A500 | (1))) && (((o)->u.i.v__).b) == 0));
}
__declspec(dllexport) const char *lua_tolstring (lua_State *L, int idx, size_t *len) {
  StkId o = index2addr(L, idx);
  if (!((((o))->u.i.tt__) == (0x7FF7A500 | (((4) | (1 << 6)))))) {
    ((void) 0);  
    if (!luaV_tostring(L, o)) {  
      if (len != ((void *)0)) *len = 0;
      ((void) 0);
      return ((void *)0);
    }
    {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
    o = index2addr(L, idx);  
    ((void) 0);
  }
  if (len != ((void *)0)) *len = (&(&((o)->u.i.v__).gc->ts)->tsv)->len;
  return ((const char *)(((&((o)->u.i.v__).gc->ts)) + 1));
}
__declspec(dllexport) size_t lua_rawlen (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  switch (((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff) & 0x0F)) {
    case 4: return (&(&((o)->u.i.v__).gc->ts)->tsv)->len;
    case 7: return (&(&((o)->u.i.v__).gc->u)->uv)->len;
    case 5: return luaH_getn((&((o)->u.i.v__).gc->h));
    default: return 0;
  }
}
__declspec(dllexport) lua_CFunction lua_tocfunction (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  if (((((o))->u.i.tt__) == (0x7FF7A500 | ((6 | (1 << 4)))))) return (((o)->u.i.v__).f);
  else if (((((o))->u.i.tt__) == (0x7FF7A500 | ((((6 | (2 << 4))) | (1 << 6))))))
    return (&((o)->u.i.v__).gc->cl.c)->f;
  else return ((void *)0);  
}
__declspec(dllexport) void *lua_touserdata (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  switch (((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff) & 0x0F)) {
    case 7: return ((&((o)->u.i.v__).gc->u) + 1);
    case 2: return (((o)->u.i.v__).p);
    default: return ((void *)0);
  }
}
__declspec(dllexport) lua_State *lua_tothread (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  return (!((((o))->u.i.tt__) == (0x7FF7A500 | (((8) | (1 << 6)))))) ? ((void *)0) : (&((o)->u.i.v__).gc->th);
}
__declspec(dllexport) const void *lua_topointer (lua_State *L, int idx) {
  StkId o = index2addr(L, idx);
  switch (((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff) & 0x3F)) {
    case 5: return (&((o)->u.i.v__).gc->h);
    case (6 | (0 << 4)): return (&((o)->u.i.v__).gc->cl.l);
    case (6 | (2 << 4)): return (&((o)->u.i.v__).gc->cl.c);
    case (6 | (1 << 4)): return ((void *)(((size_t)((((o)->u.i.v__).f)))));
    case 8: return (&((o)->u.i.v__).gc->th);
    case 7:
    case 2:
      return lua_touserdata(L, idx);
    default: return ((void *)0);
  }
}
__declspec(dllexport) void lua_pushnil (lua_State *L) {
  ((void) 0);
  (((L->top)->u.i.tt__) = (0x7FF7A500 | (0)));
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_pushnumber (lua_State *L, lua_Number n) {
  ((void) 0);
  { TValue *io_=(L->top); ((io_)->u.d__)=(n); ((void)0); };
  { if (!((((L->top)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500)) luaG_runerror(L, "C API - attempt to push a signaling NaN"); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_pushinteger (lua_State *L, lua_Integer n) {
  ((void) 0);
  { TValue *io_=(L->top); ((io_)->u.d__)=(((lua_Number)((n)))); ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_pushunsigned (lua_State *L, lua_Unsigned u) {
  lua_Number n;
  ((void) 0);
  n = (((u) <= (lua_Unsigned)2147483647) ? (lua_Number)(int)(u) : (lua_Number)(u));
  { TValue *io_=(L->top); ((io_)->u.d__)=(n); ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) const char *lua_pushlstring (lua_State *L, const char *s, size_t len) {
  TString *ts;
  ((void) 0);
  {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
  ts = luaS_newlstr(L, s, len);
  { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((ts))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
  return ((const char *)((ts) + 1));
}
__declspec(dllexport) const char *lua_pushstring (lua_State *L, const char *s) {
  if (s == ((void *)0)) {
    lua_pushnil(L);
    return ((void *)0);
  }
  else {
    TString *ts;
    ((void) 0);
    {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
    ts = luaS_new(L, s);
    { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((ts))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
    {L->top++; ((void)0);};
    ((void) 0);
    return ((const char *)((ts) + 1));
  }
}
__declspec(dllexport) const char *lua_pushvfstring (lua_State *L, const char *fmt,
                                      va_list argp) {
  const char *ret;
  ((void) 0);
  {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
  ret = luaO_pushvfstring(L, fmt, argp);
  ((void) 0);
  return ret;
}
__declspec(dllexport) const char *lua_pushfstring (lua_State *L, const char *fmt, ...) {
  const char *ret;
  va_list argp;
  ((void) 0);
  {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
  ( argp = (va_list)( &(fmt) ) + ( (sizeof(fmt) + sizeof(int) - 1) & ~(sizeof(int) - 1) ) );
  ret = luaO_pushvfstring(L, fmt, argp);
  ( argp = (va_list)0 );
  ((void) 0);
  return ret;
}
__declspec(dllexport) void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n) {
  ((void) 0);
  if (n == 0) {
    { TValue *io=(L->top); ((io)->u.i.v__).f=(fn); (((io)->u.i.tt__) = (0x7FF7A500 | ((6 | (1 << 4))))); };
  }
  else {
    Closure *cl;
    ((void)0);
    ((void)0);
    {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
    cl = luaF_newCclosure(L, n);
    cl->c.f = fn;
    L->top -= n;
    while (n--)
      { const TValue *o2_=(L->top + n); TValue *o1_=(&cl->c.upvalue[n]); o1_->u = o2_->u; ((void)0); };
    { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((cl))); (((io)->u.i.tt__) = (0x7FF7A500 | ((((6 | (2 << 4))) | (1 << 6))))); ((void)0); };
  }
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_pushboolean (lua_State *L, int b) {
  ((void) 0);
  { TValue *io=(L->top); ((io)->u.i.v__).b=((b != 0)); (((io)->u.i.tt__) = (0x7FF7A500 | (1))); };  
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_pushlightuserdata (lua_State *L, void *p) {
  ((void) 0);
  { TValue *io=(L->top); ((io)->u.i.v__).p=(p); (((io)->u.i.tt__) = (0x7FF7A500 | (2))); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) int lua_pushthread (lua_State *L) {
  ((void) 0);
  { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((L))); (((io)->u.i.tt__) = (0x7FF7A500 | (((8) | (1 << 6))))); ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
  return ((L->l_G)->mainthread == L);
}
__declspec(dllexport) void lua_getglobal (lua_State *L, const char *var) {
  Table *reg = (&((&(L->l_G)->l_registry)->u.i.v__).gc->h);
  const TValue *gt;  
  ((void) 0);
  gt = luaH_getint(reg, 2);
  { TValue *io=(L->top++); ((io)->u.i.v__).gc=((GCObject *)((luaS_new(L, var)))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
  luaV_gettable(L, gt, L->top - 1, L->top - 1);
  ((void) 0);
}
__declspec(dllexport) void lua_gettable (lua_State *L, int idx) {
  StkId t;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);
  luaV_gettable(L, t, L->top - 1, L->top - 1);
  ((void) 0);
}
__declspec(dllexport) void lua_getfield (lua_State *L, int idx, const char *k) {
  StkId t;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);
  { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((luaS_new(L, k)))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
  {L->top++; ((void)0);};
  luaV_gettable(L, t, L->top - 1, L->top - 1);
  ((void) 0);
}
__declspec(dllexport) void lua_rawget (lua_State *L, int idx) {
  StkId t;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);

  {
	  const TValue *o2_=(luaH_get((&((t)->u.i.v__).gc->h), L->top - 1));
	  TValue *o1_=(L->top - 1); 
	  o1_->u = o2_->u;
	  ((void)0);
  };

  ((void) 0);
}
__declspec(dllexport) void lua_rawgeti (lua_State *L, int idx, int n) {
  StkId t;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);
  {
	  const TValue *o2_=(luaH_getint((&((t)->u.i.v__).gc->h), n)); 
	  TValue *o1_=(L->top); 
	  o1_->u = o2_->u;
	  ((void)0);
  };
  {
	  L->top++;
	  ((void)0);
  };
  ((void) 0);
}
__declspec(dllexport) void lua_rawgetp (lua_State *L, int idx, const void *p) {
  StkId t;
  TValue k;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);
  { TValue *io=(&k); ((io)->u.i.v__).p=(((void *)(p))); (((io)->u.i.tt__) = (0x7FF7A500 | (2))); };
  { const TValue *o2_=(luaH_get((&((t)->u.i.v__).gc->h), &k)); TValue *o1_=(L->top); o1_->u = o2_->u; ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_createtable (lua_State *L, int narray, int nrec) {
  Table *t;
  ((void) 0);
  {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
  t = luaH_new(L);
  { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((t))); (((io)->u.i.tt__) = (0x7FF7A500 | (((5) | (1 << 6))))); ((void)0); };
  {L->top++; ((void)0);};
  if (narray > 0 || nrec > 0)
    luaH_resize(L, t, narray, nrec);
  ((void) 0);
}
__declspec(dllexport) int lua_getmetatable (lua_State *L, int objindex) {
  const TValue *obj;
  Table *mt = ((void *)0);
  int res;
  ((void) 0);
  obj = index2addr(L, objindex);
  switch (((((((obj)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((obj)->u.i.tt__) & 0xff) & 0x0F)) {
    case 5:
      mt = (&((obj)->u.i.v__).gc->h)->metatable;
      break;
    case 7:
      mt = (&(&((obj)->u.i.v__).gc->u)->uv)->metatable;
      break;
    default:
      mt = (L->l_G)->mt[((((((obj)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((obj)->u.i.tt__) & 0xff) & 0x0F)];
      break;
  }
  if (mt == ((void *)0))
    res = 0;
  else {
    { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((mt))); (((io)->u.i.tt__) = (0x7FF7A500 | (((5) | (1 << 6))))); ((void)0); };
    {L->top++; ((void)0);};
    res = 1;
  }
  ((void) 0);
  return res;
}
__declspec(dllexport) void lua_getuservalue (lua_State *L, int idx) {
  StkId o;
  ((void) 0);
  o = index2addr(L, idx);
  ((void)0);
  ((void)0);
  if ((&(&((o)->u.i.v__).gc->u)->uv)->env) {
    { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)(((&(&((o)->u.i.v__).gc->u)->uv)->env))); (((io)->u.i.tt__) = (0x7FF7A500 | (((5) | (1 << 6))))); ((void)0); };
  } else
    (((L->top)->u.i.tt__) = (0x7FF7A500 | (0)));
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) void lua_setglobal (lua_State *L, const char *var) {
  Table *reg = (&((&(L->l_G)->l_registry)->u.i.v__).gc->h);
  const TValue *gt;  
  ((void) 0);
  ((void)0);
  gt = luaH_getint(reg, 2);
  { TValue *io=(L->top++); ((io)->u.i.v__).gc=((GCObject *)((luaS_new(L, var)))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
  luaV_settable(L, gt, L->top - 1, L->top - 2);
  L->top -= 2;  
  ((void) 0);
}
__declspec(dllexport) void lua_settable (lua_State *L, int idx) {
  StkId t;
  ((void) 0);
  ((void)0);
  t = index2addr(L, idx);
  ((void)0);
  luaV_settable(L, t, L->top - 2, L->top - 1);
  L->top -= 2;  
  ((void) 0);
}
__declspec(dllexport) void lua_setfield (lua_State *L, int idx, const char *k) {
  StkId t;
  ((void) 0);
  ((void)0);
  t = index2addr(L, idx);
  ((void)0);
  { TValue *io=(L->top++); ((io)->u.i.v__).gc=((GCObject *)((luaS_new(L, k)))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
  luaV_settable(L, t, L->top - 1, L->top - 2);
  L->top -= 2;  
  ((void) 0);
}
__declspec(dllexport) void lua_rawset (lua_State *L, int idx) {
  StkId t;
  ((void) 0);
  ((void)0);
  t = index2addr(L, idx);
  ((void)0);
  { const TValue *o2_=(L->top-1); TValue *o1_=(luaH_set(L, (&((t)->u.i.v__).gc->h), L->top-2)); o1_->u = o2_->u; ((void)0); };
  (((&((t)->u.i.v__).gc->h))->flags = 0);
  { if ((((((((L->top-1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((L->top-1)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((L->top-1)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)(((((t)->u.i.v__).gc))))))->gch.marked) & ((1<<(2))))) luaC_barrierback_(L,(((t)->u.i.v__).gc)); };
  L->top -= 2;
  ((void) 0);
}
__declspec(dllexport) void lua_rawseti (lua_State *L, int idx, int n) {
  StkId t;
  ((void) 0);
  ((void)0);
  t = index2addr(L, idx);
  ((void)0);
  luaH_setint(L, (&((t)->u.i.v__).gc->h), n, L->top - 1);
  { if ((((((((L->top-1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((L->top-1)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((L->top-1)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)(((((t)->u.i.v__).gc))))))->gch.marked) & ((1<<(2))))) luaC_barrierback_(L,(((t)->u.i.v__).gc)); };
  L->top--;
  ((void) 0);
}
__declspec(dllexport) void lua_rawsetp (lua_State *L, int idx, const void *p) {
  StkId t;
  TValue k;
  ((void) 0);
  ((void)0);
  t = index2addr(L, idx);
  ((void)0);
  { TValue *io=(&k); ((io)->u.i.v__).p=(((void *)(p))); (((io)->u.i.tt__) = (0x7FF7A500 | (2))); };
  { const TValue *o2_=(L->top - 1); TValue *o1_=(luaH_set(L, (&((t)->u.i.v__).gc->h), &k)); o1_->u = o2_->u; ((void)0); };
  { if ((((((((L->top - 1)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((L->top - 1)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((L->top - 1)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)(((((t)->u.i.v__).gc))))))->gch.marked) & ((1<<(2))))) luaC_barrierback_(L,(((t)->u.i.v__).gc)); };
  L->top--;
  ((void) 0);
}
__declspec(dllexport) int lua_setmetatable (lua_State *L, int objindex) {
  TValue *obj;
  Table *mt;
  ((void) 0);
  ((void)0);
  obj = index2addr(L, objindex);
  ((void)0);
  if (((((L->top - 1))->u.i.tt__) == (0x7FF7A500 | (0))))
    mt = ((void *)0);
  else {
    ((void)0);
    mt = (&((L->top - 1)->u.i.v__).gc->h);
  }
  switch (((((((obj)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((obj)->u.i.tt__) & 0xff) & 0x0F)) {
    case 5: {
      (&((obj)->u.i.v__).gc->h)->metatable = mt;
      if (mt)
        { if (((((((GCObject *)((mt)))))->gch.marked) & (((1<<(0)) | (1<<(1))))) && ((((((GCObject *)(((((obj)->u.i.v__).gc))))))->gch.marked) & ((1<<(2))))) luaC_barrierback_(L,(((obj)->u.i.v__).gc)); };
        luaC_checkfinalizer(L, (((obj)->u.i.v__).gc), mt);
      break;
    }
    case 7: {
      (&(&((obj)->u.i.v__).gc->u)->uv)->metatable = mt;
      if (mt) {
        { if (((((((GCObject *)((mt)))))->gch.marked) & (((1<<(0)) | (1<<(1))))) && ((((((GCObject *)(((&((obj)->u.i.v__).gc->u))))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)(((&((obj)->u.i.v__).gc->u))))),(((GCObject *)((mt))))); };
        luaC_checkfinalizer(L, (((obj)->u.i.v__).gc), mt);
      }
      break;
    }
    default: {
      (L->l_G)->mt[((((((obj)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((obj)->u.i.tt__) & 0xff) & 0x0F)] = mt;
      break;
    }
  }
  L->top--;
  ((void) 0);
  return 1;
}
__declspec(dllexport) void lua_setuservalue (lua_State *L, int idx) {
  StkId o;
  ((void) 0);
  ((void)0);
  o = index2addr(L, idx);
  ((void)0);
  ((void)0);
  if (((((L->top - 1))->u.i.tt__) == (0x7FF7A500 | (0))))
    (&(&((o)->u.i.v__).gc->u)->uv)->env = ((void *)0);
  else {
    ((void)0);
    (&(&((o)->u.i.v__).gc->u)->uv)->env = (&((L->top - 1)->u.i.v__).gc->h);
    { if (((((((GCObject *)(((&((L->top - 1)->u.i.v__).gc->h))))))->gch.marked) & (((1<<(0)) | (1<<(1))))) && ((((((GCObject *)(((((o)->u.i.v__).gc))))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)(((((o)->u.i.v__).gc))))),(((GCObject *)(((&((L->top - 1)->u.i.v__).gc->h)))))); };
  }
  L->top--;
  ((void) 0);
}
__declspec(dllexport) int lua_getctx (lua_State *L, int *ctx) {
  if (L->ci->callstatus & (1<<3)) {
    if (ctx) *ctx = L->ci->u.c.ctx;
    return L->ci->u.c.status;
  }
  else return 0;
}
__declspec(dllexport) void lua_callk (lua_State *L, int nargs, int nresults, int ctx,
                        lua_CFunction k) {
  StkId func;
  ((void) 0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  func = L->top - (nargs+1);
  if (k != ((void *)0) && L->nny == 0) {  
    L->ci->u.c.k = k;  
    L->ci->u.c.ctx = ctx;  
    luaD_call(L, func, nresults, 1);  
  }
  else  
    luaD_call(L, func, nresults, 0);  
  { if ((nresults) == (-1) && L->ci->top < L->top) L->ci->top = L->top; };
  ((void) 0);
}
struct CallS {  
  StkId func;
  int nresults;
};
static void f_call (lua_State *L, void *ud) {
  struct CallS *c = ((struct CallS *)(ud));
  luaD_call(L, c->func, c->nresults, 0);
}
__declspec(dllexport) int lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc,
                        int ctx, lua_CFunction k) {
  struct CallS c;
  int status;
  ptrdiff_t func;
  ((void) 0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  if (errfunc == 0)
    func = 0;
  else {
    StkId o = index2addr(L, errfunc);
    ((void)0);
    func = ((char *)(o) - (char *)L->stack);
  }
  c.func = L->top - (nargs+1);  
  if (k == ((void *)0) || L->nny > 0) {  
    c.nresults = nresults;  
    status = luaD_pcall(L, f_call, &c, ((char *)(c.func) - (char *)L->stack), func);
  }
  else {  
    CallInfo *ci = L->ci;
    ci->u.c.k = k;  
    ci->u.c.ctx = ctx;  
    
    ci->u.c.extra = ((char *)(c.func) - (char *)L->stack);
    ci->u.c.old_allowhook = L->allowhook;
    ci->u.c.old_errfunc = L->errfunc;
    L->errfunc = func;
    
    ci->callstatus |= (1<<4);
    luaD_call(L, c.func, nresults, 1);  
    ci->callstatus &= ~(1<<4);
    L->errfunc = ci->u.c.old_errfunc;
    status = 0;  
  }
  { if ((nresults) == (-1) && L->ci->top < L->top) L->ci->top = L->top; };
  ((void) 0);
  return status;
}
__declspec(dllexport) int lua_load (lua_State *L, lua_Reader reader, void *data,
                      const char *chunkname, const char *mode) {
  ZIO z;
  int status;
  ((void) 0);
  if (!chunkname) chunkname = "?";
  luaZ_init(L, &z, reader, data);
  status = luaD_protectedparser(L, &z, chunkname, mode);
  if (status == 0) {  
    LClosure *f = (&((L->top - 1)->u.i.v__).gc->cl.l);  
    if (f->nupvalues == 1) {  
      
      Table *reg = (&((&(L->l_G)->l_registry)->u.i.v__).gc->h);
      const TValue *gt = luaH_getint(reg, 2);
      
      { const TValue *o2_=(gt); TValue *o1_=(f->upvals[0]->v); o1_->u = o2_->u; ((void)0); };
      { if ((((((((gt)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((gt)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((gt)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)((f->upvals[0])))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)((f->upvals[0])))),(((gt)->u.i.v__).gc)); };
    }
  }
  ((void) 0);
  return status;
}
__declspec(dllexport) int lua_dump (lua_State *L, lua_Writer writer, void *data) {
  int status;
  TValue *o;
  ((void) 0);
  ((void)0);
  o = L->top - 1;
  if (((((o))->u.i.tt__) == (0x7FF7A500 | ((((6 | (0 << 4))) | (1 << 6))))))
    status = luaU_dump(L, ((&((o)->u.i.v__).gc->cl.l)->p), writer, data, 0);
  else
    status = 1;
  ((void) 0);
  return status;
}
__declspec(dllexport) int  lua_status (lua_State *L) {
  return L->status;
}
__declspec(dllexport) int lua_gc (lua_State *L, int what, int data) {
  int res = 0;
  global_State *g;
  ((void) 0);
  g = (L->l_G);
  switch (what) {
    case 0: {
      g->gcrunning = 0;
      break;
    }
    case 1: {
      luaE_setdebt(g, 0);
      g->gcrunning = 1;
      break;
    }
    case 2: {
      luaC_fullgc(L, 0);
      break;
    }
    case 3: {
      
      res = ((int)((((g)->totalbytes + (g)->GCdebt) >> 10)));
      break;
    }
    case 4: {
      res = ((int)((((g)->totalbytes + (g)->GCdebt) & 0x3ff)));
      break;
    }
    case 5: {
      if (g->gckind == 2) {  
        res = (g->lastmajormem == 0);  
        luaC_forcestep(L);  
      }
      else {
        while (data-- >= 0) {
          luaC_forcestep(L);
          if (g->gcstate == 5) {  
            res = 1;  
            break;
          }
        }
      }
      break;
    }
    case 6: {
      res = g->gcpause;
      g->gcpause = data;
      break;
    }
    case 8: {
      res = g->gcmajorinc;
      g->gcmajorinc = data;
      break;
    }
    case 7: {
      res = g->gcstepmul;
      g->gcstepmul = data;
      break;
    }
    case 9: {
      res = g->gcrunning;
      break;
    }
    case 10: {  
      luaC_changemode(L, 2);
      break;
    }
    case 11: {  
      luaC_changemode(L, 0);
      break;
    }
    default: res = -1;  
  }
  ((void) 0);
  return res;
}
__declspec(dllexport) int lua_error (lua_State *L) {
  ((void) 0);
  ((void)0);
  luaG_errormsg(L);
  ((void) 0);
  return 0;  
}
__declspec(dllexport) int lua_next (lua_State *L, int idx) {
  StkId t;
  int more;
  ((void) 0);
  t = index2addr(L, idx);
  ((void)0);
  more = luaH_next(L, (&((t)->u.i.v__).gc->h), L->top - 1);
  if (more) {
    {L->top++; ((void)0);};
  }
  else  
    L->top -= 1;  
  ((void) 0);
  return more;
}
__declspec(dllexport) void lua_concat (lua_State *L, int n) {
  ((void) 0);
  ((void)0);
  if (n >= 2) {
    {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
    luaV_concat(L, n);
  }
  else if (n == 0) {  
    { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((luaS_newlstr(L, "", 0)))); (((io)->u.i.tt__) = (0x7FF7A500 | (((4) | (1 << 6))))); ((void)0); };
    {L->top++; ((void)0);};
  }
  
  ((void) 0);
}
__declspec(dllexport) void lua_len (lua_State *L, int idx) {
  StkId t;
  ((void) 0);
  t = index2addr(L, idx);
  luaV_objlen(L, L->top, t);
  {L->top++; ((void)0);};
  ((void) 0);
}
__declspec(dllexport) lua_Alloc lua_getallocf (lua_State *L, void **ud) {
  lua_Alloc f;
  ((void) 0);
  if (ud) *ud = (L->l_G)->ud;
  f = (L->l_G)->frealloc;
  ((void) 0);
  return f;
}
__declspec(dllexport) void lua_setallocf (lua_State *L, lua_Alloc f, void *ud) {
  ((void) 0);
  (L->l_G)->ud = ud;
  (L->l_G)->frealloc = f;
  ((void) 0);
}
__declspec(dllexport) void *lua_newuserdata (lua_State *L, size_t size) {
  Udata *u;
  ((void) 0);
  {if ((L->l_G)->GCdebt > 0) {luaC_step(L);;}; ((void)0);};
  u = luaS_newudata(L, size, ((void *)0));
  { TValue *io=(L->top); ((io)->u.i.v__).gc=((GCObject *)((u))); (((io)->u.i.tt__) = (0x7FF7A500 | (((7) | (1 << 6))))); ((void)0); };
  {L->top++; ((void)0);};
  ((void) 0);
  return u + 1;
}
static const char *aux_upvalue (StkId fi, int n, TValue **val,
                                GCObject **owner) {
  switch (((((((fi)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((fi)->u.i.tt__) & 0xff) & 0x3F)) {
    case (6 | (2 << 4)): {  
      CClosure *f = (&((fi)->u.i.v__).gc->cl.c);
      if (!(1 <= n && n <= f->nupvalues)) return ((void *)0);
      *val = &f->upvalue[n-1];
      if (owner) *owner = (((GCObject *)((f))));
      return "";
    }
    case (6 | (0 << 4)): {  
      LClosure *f = (&((fi)->u.i.v__).gc->cl.l);
      TString *name;
      Proto *p = f->p;
      if (!(1 <= n && n <= p->sizeupvalues)) return ((void *)0);
      *val = f->upvals[n-1]->v;
      if (owner) *owner = (((GCObject *)((f->upvals[n - 1]))));
      name = p->upvalues[n-1].name;
      return (name == ((void *)0)) ? "" : ((const char *)((name) + 1));
    }
    default: return ((void *)0);  
  }
}
__declspec(dllexport) const char *lua_getupvalue (lua_State *L, int funcindex, int n) {
  const char *name;
  TValue *val = ((void *)0);  
  ((void) 0);
  name = aux_upvalue(index2addr(L, funcindex), n, &val, ((void *)0));
  if (name) {
    { const TValue *o2_=(val); TValue *o1_=(L->top); o1_->u = o2_->u; ((void)0); };
    {L->top++; ((void)0);};
  }
  ((void) 0);
  return name;
}
__declspec(dllexport) const char *lua_setupvalue (lua_State *L, int funcindex, int n) {
  const char *name;
  TValue *val = ((void *)0);  
  GCObject *owner = ((void *)0);  
  StkId fi;
  ((void) 0);
  fi = index2addr(L, funcindex);
  ((void)0);
  name = aux_upvalue(fi, n, &val, &owner);
  if (name) {
    L->top--;
    { const TValue *o2_=(L->top); TValue *o1_=(val); o1_->u = o2_->u; ((void)0); };
    { if ((((((((L->top)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((L->top)->u.i.tt__) & 0xff) & (1 << 6)) && ((((((L->top)->u.i.v__).gc))->gch.marked) & (((1<<(0)) | (1<<(1)))))) && ((((((GCObject *)((owner)))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)((owner)))),(((L->top)->u.i.v__).gc)); };
  }
  ((void) 0);
  return name;
}
static UpVal **getupvalref (lua_State *L, int fidx, int n, LClosure **pf) {
  LClosure *f;
  StkId fi = index2addr(L, fidx);
  ((void)0);
  f = (&((fi)->u.i.v__).gc->cl.l);
  ((void)0);
  if (pf) *pf = f;
  return &f->upvals[n - 1];  
}
__declspec(dllexport) void *lua_upvalueid (lua_State *L, int fidx, int n) {
  StkId fi = index2addr(L, fidx);
  switch (((((((fi)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((fi)->u.i.tt__) & 0xff) & 0x3F)) {
    case (6 | (0 << 4)): {  
      return *getupvalref(L, fidx, n, ((void *)0));
    }
    case (6 | (2 << 4)): {  
      CClosure *f = (&((fi)->u.i.v__).gc->cl.c);
      ((void)0);
      return &f->upvalue[n - 1];
    }
    default: {
      ((void)0);
      return ((void *)0);
    }
  }
}
__declspec(dllexport) void lua_upvaluejoin (lua_State *L, int fidx1, int n1,
                                            int fidx2, int n2) {
  LClosure *f1;
  UpVal **up1 = getupvalref(L, fidx1, n1, &f1);
  UpVal **up2 = getupvalref(L, fidx2, n2, ((void *)0));
  *up1 = *up2;
  {
	  if (((((((GCObject *)((*up2)))))->gch.marked) & (((1<<(0)) | (1<<(1))))) && ((((((GCObject *)((f1)))))->gch.marked) & ((1<<(2))))) luaC_barrier_(L,(((GCObject *)((f1)))),(((GCObject *)((*up2)))));
  };
}
```