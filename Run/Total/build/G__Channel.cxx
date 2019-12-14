// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__Channel

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/home/shenqiuping/RPC_Anal/Smooth/include/Channel.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Channel(void *p = 0);
   static void *newArray_Channel(Long_t size, void *p);
   static void delete_Channel(void *p);
   static void deleteArray_Channel(void *p);
   static void destruct_Channel(void *p);
   static void streamer_Channel(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Channel*)
   {
      ::Channel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Channel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Channel", ::Channel::Class_Version(), "Channel.hpp", 6,
                  typeid(::Channel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Channel::Dictionary, isa_proxy, 16,
                  sizeof(::Channel) );
      instance.SetNew(&new_Channel);
      instance.SetNewArray(&newArray_Channel);
      instance.SetDelete(&delete_Channel);
      instance.SetDeleteArray(&deleteArray_Channel);
      instance.SetDestructor(&destruct_Channel);
      instance.SetStreamerFunc(&streamer_Channel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Channel*)
   {
      return GenerateInitInstanceLocal((::Channel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Channel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Channel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Channel::Class_Name()
{
   return "Channel";
}

//______________________________________________________________________________
const char *Channel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Channel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Channel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Channel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Channel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Channel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Channel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Channel*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Channel::Streamer(TBuffer &R__b)
{
   // Stream an object of class Channel.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> RecordLength;
      R__b >> Number;
      { TString R__str; R__str.Streamer(R__b); Name = R__str.Data(); }
      R__b >> TriggerTimeTag;
      R__b >> DCoffset;
      R__b >> StartIndexCell;
      R__b >> Group;
      {
         vector<double> &R__stl =  Data;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<double> &R__stl =  Time;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b.CheckByteCount(R__s, R__c, Channel::IsA());
   } else {
      R__c = R__b.WriteVersion(Channel::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << RecordLength;
      R__b << Number;
      { TString R__str = Name.c_str(); R__str.Streamer(R__b);}
      R__b << TriggerTimeTag;
      R__b << DCoffset;
      R__b << StartIndexCell;
      R__b << Group;
      {
         vector<double> &R__stl =  Data;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<double> &R__stl =  Time;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Channel(void *p) {
      return  p ? new(p) ::Channel : new ::Channel;
   }
   static void *newArray_Channel(Long_t nElements, void *p) {
      return p ? new(p) ::Channel[nElements] : new ::Channel[nElements];
   }
   // Wrapper around operator delete
   static void delete_Channel(void *p) {
      delete ((::Channel*)p);
   }
   static void deleteArray_Channel(void *p) {
      delete [] ((::Channel*)p);
   }
   static void destruct_Channel(void *p) {
      typedef ::Channel current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Channel(TBuffer &buf, void *obj) {
      ((::Channel*)obj)->::Channel::Streamer(buf);
   }
} // end of namespace ROOT for class ::Channel

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEChannelgR_Dictionary();
   static void vectorlEChannelgR_TClassManip(TClass*);
   static void *new_vectorlEChannelgR(void *p = 0);
   static void *newArray_vectorlEChannelgR(Long_t size, void *p);
   static void delete_vectorlEChannelgR(void *p);
   static void deleteArray_vectorlEChannelgR(void *p);
   static void destruct_vectorlEChannelgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Channel>*)
   {
      vector<Channel> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Channel>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Channel>", -2, "vector", 214,
                  typeid(vector<Channel>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEChannelgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Channel>) );
      instance.SetNew(&new_vectorlEChannelgR);
      instance.SetNewArray(&newArray_vectorlEChannelgR);
      instance.SetDelete(&delete_vectorlEChannelgR);
      instance.SetDeleteArray(&deleteArray_vectorlEChannelgR);
      instance.SetDestructor(&destruct_vectorlEChannelgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Channel> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Channel>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEChannelgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Channel>*)0x0)->GetClass();
      vectorlEChannelgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEChannelgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEChannelgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Channel> : new vector<Channel>;
   }
   static void *newArray_vectorlEChannelgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Channel>[nElements] : new vector<Channel>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEChannelgR(void *p) {
      delete ((vector<Channel>*)p);
   }
   static void deleteArray_vectorlEChannelgR(void *p) {
      delete [] ((vector<Channel>*)p);
   }
   static void destruct_vectorlEChannelgR(void *p) {
      typedef vector<Channel> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Channel>

namespace {
  void TriggerDictionaryInitialization_libChannel_Impl() {
    static const char* headers[] = {
"/home/shenqiuping/RPC_Anal/Smooth/include/Channel.hpp",
0
    };
    static const char* includePaths[] = {
"/home/shenqiuping/RPC_Anal/Smooth/bin/include",
"/home/zhangyulei/softwares/Root-6.16/install/include",
"/home/shenqiuping/RPC_Anal/Smooth/include",
"/home/zhangyulei/softwares/Root-6.16/install/include",
"/home/shenqiuping/RPC_Anal/Smooth/Run/Total/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libChannel dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Simple event class)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Simple event class)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Simple event class)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Simple event class)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/home/shenqiuping/RPC_Anal/Smooth/include/Channel.hpp")))  Channel;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libChannel dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/home/shenqiuping/RPC_Anal/Smooth/include/Channel.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Channel", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libChannel",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libChannel_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libChannel_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libChannel() {
  TriggerDictionaryInitialization_libChannel_Impl();
}
