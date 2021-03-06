/*
   Copyright (c) 2010 Aldo J. Nunez

   Licensed under the Apache License, Version 2.0.
   See the LICENSE text file for details.
*/

#pragma once

#include <MagoEED.h>


namespace Mago
{
    class ExprContext;


    class CVDecl : public MagoEE::Declaration
    {
        long                        mRefCount;
        CComBSTR                    mName;

    protected:
        RefPtr<ExprContext>         mSymStore;

        RefPtr<MagoST::ISession>    mSession;
        MagoST::SymInfoData         mSymInfoData;
        MagoST::ISymbolInfo*        mSymInfo;

        RefPtr<MagoEE::ITypeEnv>    mTypeEnv;

    public:
        CVDecl( 
            ExprContext* symStore,
            const MagoST::SymInfoData& infoData, 
            MagoST::ISymbolInfo* symInfo );
        virtual ~CVDecl();

        MagoST::ISymbolInfo* GetSymbol();

        virtual void AddRef();
        virtual void Release();

        virtual const wchar_t* GetName();

        //virtual bool GetType( MagoEE::Type*& type );
        virtual bool GetAddress( MagoEE::Address& addr );
        virtual bool GetOffset( int& offset );
        virtual bool GetSize( uint32_t& size );
        virtual bool GetBackingTy( MagoEE::ENUMTY& ty );
        virtual bool GetUdtKind( MagoEE::UdtKind& kind );
        virtual bool GetBaseClassOffset( Declaration* baseClass, int& offset );

        virtual bool IsField();
        virtual bool IsStaticField();
        virtual bool IsVar();
        virtual bool IsConstant();
        virtual bool IsType();
        virtual bool IsBaseClass();
        virtual bool IsRegister();

        virtual HRESULT FindObject( const wchar_t* name, MagoEE::Declaration*& decl );
        virtual bool EnumMembers( MagoEE::IEnumDeclarationMembers*& members );
        virtual HRESULT FindObjectByValue( uint64_t intVal, Declaration*& decl );
    };


    class GeneralCVDecl : public CVDecl
    {
        RefPtr<MagoEE::Type>    mType;

    public:
        GeneralCVDecl( 
            ExprContext* symStore,
            const MagoST::SymInfoData& infoData, 
            MagoST::ISymbolInfo* symInfo );

        void SetType( MagoEE::Type* type );

        virtual bool GetType( MagoEE::Type*& type );
    };


    class TypeCVDecl : public CVDecl
    {
        MagoST::TypeHandle  mTypeHandle;

    public:
        TypeCVDecl( 
            ExprContext* symStore,
            MagoST::TypeHandle typeHandle,
            const MagoST::SymInfoData& infoData, 
            MagoST::ISymbolInfo* symInfo );

        //virtual const wchar_t* GetName();

        virtual bool GetType( MagoEE::Type*& type );
        virtual bool GetSize( uint32_t& size );
        virtual bool GetBackingTy( MagoEE::ENUMTY& ty );
        virtual bool GetBaseClassOffset( Declaration* baseClass, int& offset );

        virtual HRESULT FindObject( const wchar_t* name, MagoEE::Declaration*& decl );
        virtual bool EnumMembers( MagoEE::IEnumDeclarationMembers*& members );
        virtual HRESULT FindObjectByValue( uint64_t intVal, Declaration*& decl );

    private:
        bool FindBaseClass( 
            const char* baseName, 
            size_t baseNameLen,
            MagoST::TypeHandle fieldListTH, 
            size_t fieldCount,
            int& offset );

        struct FindBaseClassParams
        {
            const char* Name;
            size_t      NameLen;
            int         OutOffset;
            bool        OutFound;
        };

        typedef bool (TypeCVDecl::*BaseClassFunc)( 
            MagoST::ISymbolInfo* memberInfo,
            MagoST::ISymbolInfo* classInfo,
            void* context );

        void ForeachBaseClass(
            MagoST::TypeHandle fieldListTH, 
            size_t fieldCount,
            BaseClassFunc functor,
            void* context
        );

        bool FindClassInList(
            MagoST::ISymbolInfo* memberInfo,
            MagoST::ISymbolInfo* classInfo,
            void* context );

        bool RecurseClasses(
            MagoST::ISymbolInfo* memberInfo,
            MagoST::ISymbolInfo* classInfo,
            void* context );
    };

    class RegisterCVDecl : public GeneralCVDecl
    {
    public:
        RegisterCVDecl( ExprContext* symStore, uint32_t reg );
        ~RegisterCVDecl();
    
        virtual bool IsRegister();

        static RegisterCVDecl* CreateRegisterSymbol( ExprContext* symStore, const char* name );
    };

    class TypeCVDeclMembers : public MagoEE::IEnumDeclarationMembers
    {
        long                        mRefCount;

        RefPtr<ExprContext>         mSymStore;
        RefPtr<MagoST::ISession>    mSession;
        MagoST::SymInfoData         mSymInfoData;
        MagoST::ISymbolInfo*        mSymInfo;

        MagoST::TypeScope           mListScope;
        uint32_t                    mCount;
        uint32_t                    mIndex;

    public:
        TypeCVDeclMembers( 
            ExprContext* symStore,
            const MagoST::SymInfoData& infoData, 
            MagoST::ISymbolInfo* symInfo );

        virtual void AddRef();
        virtual void Release();

        virtual uint32_t GetCount();
        virtual bool Next( MagoEE::Declaration*& decl );
        virtual bool Skip( uint32_t count );
        virtual bool Reset();

    private:
        uint16_t CountMembers();
        // -1 for non-printable, 0 for no more, 1 for ok
        int NextMember( MagoST::TypeScope& scope, MagoST::TypeHandle& memberTH );
    };


    class ClassRefDecl : public MagoEE::Declaration
    {
        long                        mRefCount;
        RefPtr<MagoEE::Declaration> mOrigDecl;
        RefPtr<MagoEE::ITypeEnv>    mTypeEnv;

    public:
        ClassRefDecl( Declaration* decl, MagoEE::ITypeEnv* typeEnv );

        virtual void AddRef();
        virtual void Release();

        virtual const wchar_t* GetName();

        virtual bool GetType( MagoEE::Type*& type );
        virtual bool GetAddress( MagoEE::Address& addr );
        virtual bool GetOffset( int& offset );
        virtual bool GetSize( uint32_t& size );
        virtual bool GetBackingTy( MagoEE::ENUMTY& ty );
        virtual bool GetUdtKind( MagoEE::UdtKind& kind );
        virtual bool GetBaseClassOffset( Declaration* baseClass, int& offset );

        virtual bool IsField();
        virtual bool IsStaticField();
        virtual bool IsVar();
        virtual bool IsConstant();
        virtual bool IsType();
        virtual bool IsBaseClass();
        virtual bool IsRegister();

        virtual HRESULT FindObject( const wchar_t* name, Declaration*& decl );
        virtual bool EnumMembers( MagoEE::IEnumDeclarationMembers*& members );
        virtual HRESULT FindObjectByValue( uint64_t intVal, Declaration*& decl );
    };
}
