#define INSTRUCTION_CPP
#include "instruction.h"

#include <string.h>

u4_t Instruction::getPC(){
   return(pc);
}
ByteCode *Instruction::getByteCode(){
   return(byteCode);
}

Instruction::Instruction(ConstantPoolEntry** _constantPool, ByteBuffer *_codeByteBuffer, u2_t _maxStack, u4_t *_stackMap, u2_t *_stackSize, s4_t _prevPc ){
   prevPc = _prevPc;
   stackBase = *_stackSize;
   pc = _codeByteBuffer->getOffset();
   byte_t byte= _codeByteBuffer->u1();
   byteCode = &bytecode[byte];
   switch(byteCode->immSpec){
      case ImmSpec_NONE:
         break;
      case ImmSpec_NONE_const_null:
         break;
      case ImmSpec_NONE_const_m1:
         break;
      case ImmSpec_NONE_const_0:
         break;
      case ImmSpec_NONE_const_1:
         break;
      case ImmSpec_NONE_const_2:
         break;
      case ImmSpec_NONE_const_3:
         break;
      case ImmSpec_NONE_const_4:
         break;
      case ImmSpec_NONE_const_5:
         break;
      case ImmSpec_NONE_lvti_0:
         break;
      case ImmSpec_NONE_lvti_1:
         break;
      case ImmSpec_NONE_lvti_2:
         break;
      case ImmSpec_NONE_lvti_3:
         break;
      case ImmSpec_Blvti:
         immSpec_Blvti.lvti=_codeByteBuffer->u1();
         break;
      case ImmSpec_Bcpci:
         immSpec_Bcpci.cpci=_codeByteBuffer->u1();
         break;
      case ImmSpec_Scpci:
         immSpec_Scpci.cpci= _codeByteBuffer->u2();
         break;
      case ImmSpec_Bconst:
         immSpec_Bconst.value= _codeByteBuffer->u1();
         break;
      case ImmSpec_Sconst:
         immSpec_Sconst.value= _codeByteBuffer->u2();
         break;
      case ImmSpec_Spc:
         immSpec_Spc.pc= _codeByteBuffer->s2() +pc;
         break;
      case ImmSpec_Scpfi:
         immSpec_Scpfi.cpfi= _codeByteBuffer->u2();
         break;
      case ImmSpec_ScpmiBB:
         immSpec_ScpmiBB.cpmi= _codeByteBuffer->u2();
         immSpec_ScpmiBB.b1= _codeByteBuffer->u1();
         immSpec_ScpmiBB.b2= _codeByteBuffer->u1();
         break;
      case ImmSpec_BlvtiBconst:
         immSpec_BlvtiBconst.lvti= _codeByteBuffer->u1();
         immSpec_BlvtiBconst.value= _codeByteBuffer->u1();
         break;
      case ImmSpec_Scpmi:
         immSpec_Scpmi.cpmi= _codeByteBuffer->u2();
         break;
      case ImmSpec_ScpciBdim:
         immSpec_ScpciBdim.cpci= _codeByteBuffer->u2();
         immSpec_ScpciBdim.dim= _codeByteBuffer->u1();
         break;
      case ImmSpec_Ipc:
         immSpec_Ipc.pc= _codeByteBuffer->s4()+pc;
         break;
      case ImmSpec_UNKNOWN:
         break;

   }

   length = _codeByteBuffer->getOffset()-pc;

   switch(byteCode->popSpec){
      case PopSpec_NONE:
         break;
      case PopSpec_A:
         popSpec_A.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AI:
         popSpec_AI.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AI.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AII:
         popSpec_AII.i2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AII.i1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AII.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIL:
         popSpec_AIL.l = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIL.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIL.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIF:
         popSpec_AIF.f = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIF.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIF.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AID:
         popSpec_AID.d = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AID.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AID.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIO:
         popSpec_AIO.o = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIO.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIO.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIB:
         popSpec_AIB.b = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIB.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIB.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIC:
         popSpec_AIC.c = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIC.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIC.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_AIS:
         popSpec_AIS.s = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIS.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_AIS.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_II :
         popSpec_II.i2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_II.i1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_III:
         popSpec_III.i3 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_III.i2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_III.i1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_IIII:
         popSpec_IIII.i4 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_IIII.i3 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_IIII.i2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_IIII.i1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_L:
         popSpec_L.l = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_LI:
         popSpec_LI.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_LI.l = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_LL:
         popSpec_LL.l2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_LL.l1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_F:
         popSpec_F.f = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_FF:
         popSpec_FF.f2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_FF.f1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_OO:
         popSpec_OO.o2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_OO.o1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_RA:
         popSpec_RA.a = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_RA.r = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_O:
         popSpec_O.o = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_I:
         popSpec_I.i = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_D:
         popSpec_D.d = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_DD:
         popSpec_DD.d2 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_DD.d1 = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_OFSIG:
         popSpec_OFSIG.v = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         popSpec_OFSIG.o = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_FSIG:
         popSpec_FSIG.v = _stackMap[--(*_stackSize)];
         _stackMap[*_stackSize] = -1;
         break;
      case PopSpec_UNKNOWN:
         break;
      case PopSpec_MSIG:
         {
            MethodConstantPoolEntry* method = (MethodConstantPoolEntry*)_constantPool[immSpec_Scpmi.cpmi];
            popSpec_MSIG.argc = method->getArgCount(_constantPool);
            if (popSpec_MSIG.argc>0){
               popSpec_MSIG.args = new u4_t[popSpec_MSIG.argc];
               for (int i=popSpec_MSIG.argc-1; i>=0;  i--){
                  popSpec_MSIG.args[i] = _stackMap[--(*_stackSize)];
                  _stackMap[*_stackSize] = -1;
               }
            }else{
               popSpec_MSIG.args = NULL;
            }
         }
         break;
      case PopSpec_OMSIG:
         {
            MethodConstantPoolEntry* method = (MethodConstantPoolEntry*)_constantPool[immSpec_Scpmi.cpmi];
            popSpec_OMSIG.argc = method->getArgCount(_constantPool);
            if ( popSpec_OMSIG.argc>0){
               popSpec_OMSIG.args = new u4_t[popSpec_OMSIG.argc];
               for (int i=popSpec_OMSIG.argc-1; i>=0; i--){
                  popSpec_OMSIG.args[i] = _stackMap[--(*_stackSize)];
                  _stackMap[*_stackSize] = -1;
               }
            }else{
               popSpec_OMSIG.args = NULL;

            }
            popSpec_OMSIG.o = _stackMap[--(*_stackSize)];
            _stackMap[*_stackSize] = -1;
         }
         break;
   }


   switch(byteCode->pushSpec){
      case PushSpec_NONE:
         break;
      case PushSpec_N:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_I:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_L:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_F:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_D:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_O:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_A:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_RA:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_IorForS:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_LorD:
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_II:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_III:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_IIII:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_IIIII:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_IIIIII:
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         _stackMap[(*_stackSize)++] = pc;
         break;
      case PushSpec_FSIG:
         {
            FieldConstantPoolEntry* field = (FieldConstantPoolEntry*)_constantPool[immSpec_Scpmi.cpmi];
            _stackMap[(*_stackSize)++] = pc;
         }

         break;
      case PushSpec_MSIG:
         {
            MethodConstantPoolEntry* method = (MethodConstantPoolEntry*)_constantPool[immSpec_Scpmi.cpmi];
            int retc = method->getRetCount(_constantPool);
            if (retc>0){
               _stackMap[(*_stackSize)++] = pc;
            } else {
            }
         }

         break;
      case PushSpec_UNKNOWN:
         break;
   }


}

Instruction::~Instruction(){
   switch(byteCode->pushSpec){
      case PopSpec_MSIG:
         if (popSpec_MSIG.argc>0){
            delete [] popSpec_MSIG.args;
         }
         break;
      case PopSpec_OMSIG:
         if ( popSpec_OMSIG.argc>0){
            delete [] popSpec_OMSIG.args;
         }
         break;
   }
}


void Instruction::write(FILE *_file, ConstantPoolEntry **_constantPool, LocalVariableTableAttribute *_localVariableTableAttribute){
   fprintf(_file, "%4d %-10s", pc, (char*)byteCode->name);
   switch(byteCode->immSpec){
      case ImmSpec_NONE:
         break;
      case ImmSpec_NONE_const_null:
         fprintf(_file, " NULL");
         break;
      case ImmSpec_NONE_const_m1:
         fprintf(_file, " -1");
         break;
      case ImmSpec_NONE_const_0:
         fprintf(_file, " 0");
         break;
      case ImmSpec_NONE_const_1:
         fprintf(_file, " 1");
         break;
      case ImmSpec_NONE_const_2:
         fprintf(_file, " 2");
         break;
      case ImmSpec_NONE_const_3:
         fprintf(_file, " 3");
         break;
      case ImmSpec_NONE_const_4:
         fprintf(_file, " 4");
         break;
      case ImmSpec_NONE_const_5:
         fprintf(_file, " 5");
         break;
      case ImmSpec_NONE_lvti_0:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 0, _constantPool);
            fprintf(_file, " name = %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_1:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 1, _constantPool);
            fprintf(_file, " name = %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_2:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 2, _constantPool);
            fprintf(_file, " name = %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_3:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 3, _constantPool);
            fprintf(_file, " name = %s", varName);
         }
         break;
      case ImmSpec_Blvti:
         fprintf(_file, " %d [", immSpec_Blvti.lvti);
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, immSpec_Blvti.lvti, _constantPool);
            fprintf(_file, " name = %s", varName);
         }
         fprintf(_file, " ]");
         break;
      case ImmSpec_Bcpci:
      case ImmSpec_Scpci:
         {
            int cpi = 0;
            if (byteCode->immSpec == ImmSpec_Bcpci){
               cpi = immSpec_Bcpci.cpci;
            }else{
               cpi = immSpec_Scpci.cpci;
            }
            ConstantPoolEntry* constantPoolEntry = _constantPool[cpi];
            switch (constantPoolEntry->getConstantPoolType()){
               case FLOAT:
                  fprintf(_file, " FLOAT %f", ((FloatConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case INTEGER:
                  fprintf(_file, " INTEGER %d", ((IntegerConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case DOUBLE:
                  fprintf(_file, " DOUBLE %lf", ((DoubleConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case LONG:
                  fprintf(_file, " LONG %ld", ((LongConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               default:
                  fprintf(_file, " constant pool #%d", immSpec_Bcpci.cpci);
                  break;
            }
            break;
         }
      case ImmSpec_Bconst:
         fprintf(_file, " byte %d", immSpec_Bconst.value);
         break;
      case ImmSpec_Sconst:
         fprintf(_file, " short %d", immSpec_Sconst.value);
         break;
      case ImmSpec_Spc:
         fprintf(_file, " %d", immSpec_Spc.pc);
         break;
      case ImmSpec_Scpfi:
         break;
      case ImmSpec_ScpmiBB:
         break;
      case ImmSpec_BlvtiBconst:
         break;
      case ImmSpec_Scpmi:
         break;
      case ImmSpec_ScpciBdim:
         break;
      case ImmSpec_Ipc:
         fprintf(_file, " %d", immSpec_Ipc.pc);
         break;
      case ImmSpec_UNKNOWN:
         break;

   }

   switch(byteCode->popSpec){
      case PopSpec_NONE:
         fprintf(_file, " <-- NONE");
         break;
      case PopSpec_A:
         //popSpec_A.a = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AI:
         fprintf(_file, " <-- pop ((array)%d, (int)%d)", popSpec_AI.a, popSpec_AI.i);
         //popSpec_AI.a = _stackMap[--(*_stackSize)];
         //popSpec_AI.i = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AII:
         fprintf(_file, " <-- pop ((array)%d, (int)%d, (int)%d)", popSpec_AII.a, popSpec_AII.i1, popSpec_AII.i2);
         //popSpec_AII.a = _stackMap[--(*_stackSize)];
         //popSpec_AII.i1 = _stackMap[--(*_stackSize)];
         //popSpec_AII.i2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIL:
         //popSpec_AIL.a = _stackMap[--(*_stackSize)];
         //popSpec_AIL.i = _stackMap[--(*_stackSize)];
         //popSpec_AIL.l = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIF:
         //popSpec_AIF.a = _stackMap[--(*_stackSize)];
         //popSpec_AIF.i = _stackMap[--(*_stackSize)];
         //popSpec_AIF.f = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AID:
         //popSpec_AID.a = _stackMap[--(*_stackSize)];
         //popSpec_AID.i = _stackMap[--(*_stackSize)];
         //popSpec_AID.d = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIO:
         //popSpec_AIO.a = _stackMap[--(*_stackSize)];
         //popSpec_AIO.i = _stackMap[--(*_stackSize)];
         //popSpec_AIO.o = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIB:
         //popSpec_AIB.a = _stackMap[--(*_stackSize)];
         //popSpec_AIB.i = _stackMap[--(*_stackSize)];
         //popSpec_AIB.b = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIC:
         //popSpec_AIC.a = _stackMap[--(*_stackSize)];
         //popSpec_AIC.i = _stackMap[--(*_stackSize)];
         //popSpec_AIC.c = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_AIS:
         //popSpec_AIS.a = _stackMap[--(*_stackSize)];
         //popSpec_AIS.i = _stackMap[--(*_stackSize)];
         //popSpec_AIS.s = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_II :
         fprintf(_file, " <-- ((int)%d, (int)%d)", popSpec_II.i1, popSpec_II.i2);
         //popSpec_II.i1 = _stackMap[--(*_stackSize)];
         //popSpec_II.i2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_III:
         //popSpec_III.i1 = _stackMap[--(*_stackSize)];
         //popSpec_III.i2 = _stackMap[--(*_stackSize)];
         //popSpec_III.i3 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_IIII:
         //popSpec_IIII.i1 = _stackMap[--(*_stackSize)];
         //popSpec_IIII.i2 = _stackMap[--(*_stackSize)];
         //popSpec_IIII.i3 = _stackMap[--(*_stackSize)];
         //popSpec_IIII.i4 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_L:
         //popSpec_L.l = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_LI:
         //popSpec_LI.l = _stackMap[--(*_stackSize)];
         //popSpec_LI.i = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_LL:
         //popSpec_LL.l1 = _stackMap[--(*_stackSize)];
         //popSpec_LL.l2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_F:
         fprintf(_file, " <-- ((float)%d)", popSpec_F.f);
         //popSpec_F.f = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_FF:
         fprintf(_file, " <-- ((float)%d, (float)%d)", popSpec_FF.f1, popSpec_FF.f2);
         //popSpec_FF.f1 = _stackMap[--(*_stackSize)];
         //popSpec_FF.f2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_OO:
         fprintf(_file, " <-- ((object)%d, (object)%d)", popSpec_OO.o1, popSpec_OO.o2);
         //popSpec_OO.o1 = _stackMap[--(*_stackSize)];
         //popSpec_OO.o2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_RA:
         //popSpec_RA.r = _stackMap[--(*_stackSize)];
         //popSpec_RA.a = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_O:
         fprintf(_file, " <-- ((object)%d)", popSpec_O.o);
         //popSpec_O.o = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_I:
         fprintf(_file, " <-- ((int)%d)", popSpec_I.i);
         //popSpec_I.i = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_D:
         //popSpec_D.d = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_DD:
         //popSpec_DD.d1 = _stackMap[--(*_stackSize)];
         //popSpec_DD.d2 = _stackMap[--(*_stackSize)];
         break;
      case PopSpec_OFSIG:
         break;
      case PopSpec_FSIG:
         break;
      case PopSpec_UNKNOWN:
         break;
      case PopSpec_MSIG:
         {
            fprintf(_file, " <-- ");
            if (popSpec_MSIG.argc==0){
               fprintf(_file, "NONE");
            }else{
               fprintf(_file, "(");
               for (int i=0; i<popSpec_MSIG.argc; i++){
                  if (i>0){
                     fprintf(_file, " ,");
                  }
                  fprintf(_file, "%d ", popSpec_MSIG.args[i]);
               }
               fprintf(_file, ")");
            }

            //  popSpec_MSIG.argc = method->getArgCount(_constantPool);
            //  popSpec_MSIG.args = new u4_t[popSpec_MSIG.argc];
         }
         break;
      case PopSpec_OMSIG:
         {
            fprintf(_file, " <- (%d", popSpec_OMSIG.o);
            if (popSpec_OMSIG.argc>0){
               for (int i=0; i<popSpec_OMSIG.argc; i++){
                  fprintf(_file, ", %d", popSpec_OMSIG.args[i]);
               }
            }
            fprintf(_file, ")");
            //  popSpec_OMSIG.o = _stackMap[--(*_stackSize)];
            //  popSpec_OMSIG.argc = method->getArgCount(_constantPool);
            //  popSpec_OMSIG.args = new u4_t[popSpec_OMSIG.argc];
         }
         break;
   }
}


void Instruction::treeWrite(FILE *_file, Instruction **_instructions, int _depth, ConstantPoolEntry **_constantPool, LocalVariableTableAttribute *_localVariableTableAttribute){
   for (int i=0; i<_depth; i++){
      fprintf(_file, "   ");
   }
   fprintf(_file, "%4d %-10s", pc, (char*)byteCode->name);

   switch(byteCode->immSpec){
      case ImmSpec_NONE:
         break;
      case ImmSpec_NONE_const_null:
         fprintf(_file, " NULL");
         break;
      case ImmSpec_NONE_const_m1:
         fprintf(_file, " -1");
         break;
      case ImmSpec_NONE_const_0:
         fprintf(_file, " 0");
         break;
      case ImmSpec_NONE_const_1:
         fprintf(_file, " 1");
         break;
      case ImmSpec_NONE_const_2:
         fprintf(_file, " 2");
         break;
      case ImmSpec_NONE_const_3:
         fprintf(_file, " 3");
         break;
      case ImmSpec_NONE_const_4:
         fprintf(_file, " 4");
         break;
      case ImmSpec_NONE_const_5:
         fprintf(_file, " 5");
         break;
      case ImmSpec_NONE_lvti_0:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 0, _constantPool);
            fprintf(_file, " %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_1:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 1, _constantPool);
            fprintf(_file, " %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_2:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 2, _constantPool);
            fprintf(_file, " %s", varName);
         }
         break;
      case ImmSpec_NONE_lvti_3:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, 3, _constantPool);
            fprintf(_file, " %s", varName);
         }
         break;
      case ImmSpec_Blvti:
         if (_localVariableTableAttribute !=  NULL){
            char *varName = _localVariableTableAttribute->getLocalVariableName(pc +length, immSpec_Blvti.lvti, _constantPool);
            fprintf(_file, " %s", varName);
         }
         break;
      case ImmSpec_Bcpci:
      case ImmSpec_Scpci:
         {
            int cpi = 0;
            if (byteCode->immSpec == ImmSpec_Bcpci){
               cpi = immSpec_Bcpci.cpci;
            }else{
               cpi = immSpec_Scpci.cpci;
            }
            ConstantPoolEntry* constantPoolEntry = _constantPool[cpi];
            switch (constantPoolEntry->getConstantPoolType()){
               case FLOAT:
                  fprintf(_file, " %f", ((FloatConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case INTEGER:
                  fprintf(_file, " %d", ((IntegerConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case DOUBLE:
                  fprintf(_file, " %lf", ((DoubleConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               case LONG:
                  fprintf(_file, " %ld", ((LongConstantPoolEntry*)constantPoolEntry)->getValue());
                  break;
               default:
                  fprintf(_file, " constant pool #%d", immSpec_Bcpci.cpci);
                  break;
            }
            break;
         }
      case ImmSpec_Bconst:
         fprintf(_file, " %d", immSpec_Bconst.value);
         break;
      case ImmSpec_Sconst:
         fprintf(_file, " %d", immSpec_Sconst.value);
         break;
      case ImmSpec_Spc:
         fprintf(_file, " %d", immSpec_Spc.pc);
         break;
      case ImmSpec_Scpfi:
         {
            FieldConstantPoolEntry* fieldConstantPoolEntry = (FieldConstantPoolEntry*)_constantPool[immSpec_Scpfi.cpfi];
            NameAndTypeConstantPoolEntry* nameAndTypeConstantPoolEntry = (NameAndTypeConstantPoolEntry*)_constantPool[fieldConstantPoolEntry->getNameAndTypeIndex()];
            UTF8ConstantPoolEntry* nameConstantPoolEntry = (UTF8ConstantPoolEntry*)_constantPool[nameAndTypeConstantPoolEntry->getNameIndex()];

            fprintf(_file, " %s", nameConstantPoolEntry->getUTF8());
            break;
         }
      case ImmSpec_ScpmiBB:
         break;
      case ImmSpec_BlvtiBconst:
         break;
      case ImmSpec_Scpmi:
         {
            MethodConstantPoolEntry* methodConstantPoolEntry = (MethodConstantPoolEntry*)_constantPool[immSpec_Scpmi.cpmi];
            NameAndTypeConstantPoolEntry* nameAndTypeConstantPoolEntry = (NameAndTypeConstantPoolEntry*)_constantPool[methodConstantPoolEntry->getNameAndTypeIndex()];
            UTF8ConstantPoolEntry* nameConstantPoolEntry = (UTF8ConstantPoolEntry*)_constantPool[nameAndTypeConstantPoolEntry->getNameIndex()];
            fprintf(_file, " %s", nameConstantPoolEntry->getUTF8());
            break;
         }
      case ImmSpec_ScpciBdim:
         break;
      case ImmSpec_Ipc:
         fprintf(_file, " %d", immSpec_Ipc.pc);
         break;
      case ImmSpec_UNKNOWN:
         break;

   }


   //write(_file, _constantPool, _localVariableTableAttribute);
   fprintf(_file, "\n");
   switch(byteCode->popSpec){
      case PopSpec_NONE:
         break;
      case PopSpec_A:
         _instructions[popSpec_A.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AI:
         _instructions[popSpec_AI.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AI.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AII:
         _instructions[popSpec_AII.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AII.i1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AII.i2]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIL:
         _instructions[popSpec_AIL.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIL.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIL.l]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIF:
         _instructions[popSpec_AIF.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIF.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIF.f]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AID:
         _instructions[popSpec_AID.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AID.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AID.d]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIO:
         _instructions[popSpec_AIO.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIO.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIO.o]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIB:
         _instructions[popSpec_AIB.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIB.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIB.b]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIC:
         _instructions[popSpec_AIC.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIC.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIC.c]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_AIS:
         _instructions[popSpec_AIS.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIS.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_AIS.s]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_II :
         _instructions[popSpec_II.i1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_II.i2]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_III:
         break;
      case PopSpec_IIII:
         break;
      case PopSpec_L:
         _instructions[popSpec_L.l]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_LI:
         _instructions[popSpec_LI.l]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_LI.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_LL:
         _instructions[popSpec_LL.l1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_LL.l2]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_F:
         _instructions[popSpec_F.f]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_FF:
         _instructions[popSpec_FF.f1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_FF.f2]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_OO:
         _instructions[popSpec_OO.o1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_OO.o2]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_RA:
         _instructions[popSpec_RA.r]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_RA.a]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_O:
         _instructions[popSpec_O.o]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_I:
         _instructions[popSpec_I.i]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_D:
         _instructions[popSpec_D.d]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_DD:
         _instructions[popSpec_DD.d1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         _instructions[popSpec_DD.d1]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
         break;
      case PopSpec_OFSIG:
         break;
      case PopSpec_FSIG:
         break;
      case PopSpec_UNKNOWN:
         break;
      case PopSpec_MSIG:
            if (popSpec_MSIG.argc!=0){
               for (int i=0; i<popSpec_MSIG.argc; i++){
                  _instructions[popSpec_MSIG.args[i]]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
               }
            }
         break;
      case PopSpec_OMSIG:
            _instructions[popSpec_OMSIG.o]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
            if (popSpec_OMSIG.argc>0){
               for (int i=0; i<popSpec_OMSIG.argc; i++){
                  _instructions[popSpec_OMSIG.args[i]]->treeWrite(_file, _instructions, _depth+1, _constantPool, _localVariableTableAttribute);
               }
            }
         break;
   }
}

s4_t Instruction::getPrevPC(){
   return(prevPc);
}

u4_t Instruction::getNextPC(){
   return(pc+length);
}

u2_t Instruction::getStackBase(){
   return(stackBase);
}

void Decoder::list(u1_t* buf, u4_t len){
   fprintf(stdout, "inside list\n");
}



