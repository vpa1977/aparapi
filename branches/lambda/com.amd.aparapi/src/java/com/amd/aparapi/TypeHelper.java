package com.amd.aparapi;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;


public class TypeHelper{

   static final char VOID = 'V';

   static final char BOOLEAN = 'Z';

   static final char STRING = 's'; // Annotation constantpool entries use this

   static final char ENUM = 'e'; // Annotation constantpool entries use this

   static final char CLASS = 'c'; // Annotation constantpool entries use this

   static final char ANNOTATION = '@'; // Annotation constantpool entries use this

   static final char ARRAY = 'a'; // Annotation constantpool entries use this

   static final char BYTE = 'B';

   static final char CHAR = 'C';

   static final char SHORT = 'S';

   static final char INT = 'I';

   static final char LONG = 'J';

   static final char FLOAT = 'F';

   static final char DOUBLE = 'D';

   static final char ARRAY_DIM = '[';

   static final char CLASS_START = 'L';

   static final char ARG_START = '(';

   static final char CLASS_END = ';';

   static final char ARG_END = ')';

   static final char SLASH = '/';

   static final char DOT = '.';

   static final char UNDERSCORE = '_';


   /**
    * Convert a given JNI character type (say 'I') to its type name ('int').
    *
    * @param _typeChar
    * @return either a mapped type name or null if no mapping exists.
    */
   static String typeName(char _typeChar){
      String returnName = null;
      switch(_typeChar){
         case VOID:
            returnName = "void";
            break;
         case INT:
            returnName = "int";
            break;
         case DOUBLE:
            returnName = "double";
            break;
         case FLOAT:
            returnName = "float";
            break;
         case SHORT:
            returnName = "short";
            break;
         case CHAR:
            returnName = "char";
            break;
         case BYTE:
            returnName = "byte";
            break;
         case LONG:
            returnName = "long";
            break;
         case BOOLEAN:
            returnName = "boolean";
            break;
      }
      return (returnName);
   }

   static String convert(String _string){
      return (convert(_string, "", false));
   }

   static String convert(String _string, String _insert){
      return (convert(_string, _insert, false));
   }

   static String convert(String _string, String _insert, boolean _showFullClassName){
      Stack<String> stringStack = new Stack<String>();
      Stack<String> methodStack = null;
      int length = _string.length();
      char[] chars = _string.toCharArray();
      int i = 0;
      boolean inArray = false;
      boolean inMethod = false;
      boolean inArgs = false;
      int args = 0;
      while(i < length){
         switch(chars[i]){
            case CLASS_START:{
               StringBuilder classNameBuffer = new StringBuilder();
               i++;
               while((i < length) && chars[i] != CLASS_END){
                  if(chars[i] == SLASH){
                     classNameBuffer.append(DOT);
                  }else{
                     classNameBuffer.append(chars[i]);
                  }
                  i++;
               }
               i++; // step over CLASS_END
               String className = classNameBuffer.toString();
               if(_showFullClassName){
                  if(className.startsWith("java.lang")){
                     className = className.substring("java.lang.".length());
                  }
               }else{
                  int lastDot = className.lastIndexOf(DOT);
                  if(lastDot > 0){
                     className = className.substring(lastDot + 1);
                  }
               }
               if(inArray){
                  // swap the stack items
                  String popped = stringStack.pop();
                  if(inArgs && args > 0){
                     stringStack.push(", ");
                  }
                  stringStack.push(className);
                  stringStack.push(popped);
                  inArray = false;
               }else{
                  if(inArgs && args > 0){
                     stringStack.push(", ");
                  }
                  stringStack.push(className);
               }
               args++;
            }
            break;
            case ARRAY_DIM:{
               StringBuilder arrayDims = new StringBuilder();
               while((i < length) && chars[i] == ARRAY_DIM){
                  arrayDims.append("[]");
                  i++;
               }
               stringStack.push(arrayDims.toString());
               inArray = true;
            }
            break;
            case VOID:
            case INT:
            case DOUBLE:
            case FLOAT:
            case SHORT:
            case CHAR:
            case BYTE:
            case LONG:
            case BOOLEAN:{
               if(inArray){
                  // swap the stack items
                  String popped = stringStack.pop();
                  if(inArgs && args > 0){
                     stringStack.push(", ");
                  }
                  stringStack.push(typeName(chars[i]));
                  stringStack.push(popped);
                  inArray = false;
               }else{
                  if(inArgs && args > 0){
                     stringStack.push(", ");
                  }
                  stringStack.push(typeName(chars[i]));
               }
               i++; // step over this
            }
            break;
            case ARG_START:{
               stringStack.push("(");
               i++; // step over this
               inArgs = true;
               args = 0;
            }
            break;
            case ARG_END:{
               inMethod = true;
               inArgs = false;
               stringStack.push(")");
               methodStack = stringStack;
               stringStack = new Stack<String>();
               i++; // step over this
            }
            break;
         }
      }

      StringBuilder returnValue = new StringBuilder();
      for(String s : stringStack){
         returnValue.append(s);
         returnValue.append(" ");

      }
      if(inMethod){
         for(String s : methodStack){
            returnValue.append(s);
            returnValue.append(" ");
         }
      }else{
         returnValue.append(_insert);
      }
      return (returnValue.toString());
   }

   /**
    * Convert a signature form "Lpackage/Name;" or array form to dot class form.
    * <p/>
    * signatureToDotClassName("Lpackage/Outer$Name;", 0) -> "package.Outer.Name"
    * signatureToDotClassName("[Lpackage/Outer$Name;", 1) -> "package.Outer.Name"
    *
    * @param _signature
    * @param _dims
    * @return
    */
   public static String signatureToDotClassName(String _signature, int _dims){
      String  dotClassName =  slashClassNameToDotClassName(_signature.substring(1 + _dims, _signature.length() - 1));
      return (dotClassName);
   }

   public static String signatureToMangledClassName(String _signature, int _dims){
      String mangledClassName =  slashClassNameToMangledClassName(_signature.substring(1 + _dims, _signature.length() - 1));
      return (mangledClassName);
   }

   /**
    * @param _dotClassName
    * @param _dims
    * @return
    */
   public static String dotClassNameToSignature(String _dotClassName, int _dims){
      StringBuilder sb = new StringBuilder();
      for(int i = 0; i < _dims; i++){
         sb.append(ARRAY_DIM);
      }
      sb.append(CLASS_START).append(dotClassNameToSlashClassName(_dotClassName)).append(CLASS_END);
      return (sb.toString());
   }

   public static String dotClassNameToMangledClassName(String _dotClassName){
      return (_dotClassName.replace(DOT, UNDERSCORE));
   }

   /**
    * @param _dotClassName
    * @return
    */
   public static String dotClassNameToSlashClassName(String _dotClassName){
      return (_dotClassName.replace(DOT, SLASH));
   }

   /**
    * @param _slashClassName
    * @return
    */
   public static String slashClassNameToDotClassName(String _slashClassName){
      return (_slashClassName.replace(SLASH, DOT));
   }

   /**
    * @param _slashClassName
    * @return
    */
   public static String slashClassNameToMangledClassName(String _slashClassName){
      return (_slashClassName.replace(SLASH, UNDERSCORE));
   }

   static class Type{
      private int arrayDimensions = 0;

      Type(String _type){
         type = _type;

         while(type.charAt(arrayDimensions) == ARRAY_DIM){
            arrayDimensions++;
         }
         type = type.substring(arrayDimensions);
      }

      public Type(InstructionSet.StoreSpec _storeSpec) {
         switch(_storeSpec){
             case A:type = "[?"; arrayDimensions = 1; break;
             default: type = _storeSpec.name();
         }

      }
      public Type(Field _field){
         this(_field.getType());
      }

      public Type(Class<?> _clazz){
         Class componentType;
         String arrayPrefix = "";
         if(_clazz.isArray()){
            componentType = _clazz.getComponentType();
            arrayDimensions = _clazz.getName().lastIndexOf('[') + 1;
            arrayPrefix = _clazz.getName().substring(0, arrayDimensions);
         }else{
            componentType = _clazz;
         }


         if(componentType == int.class){
            type = arrayPrefix + INT;
         }else if(componentType == float.class){
            type = arrayPrefix + FLOAT;
         }else if(componentType == double.class){
            type = arrayPrefix + DOUBLE;
         }else if(componentType == long.class){
            type = arrayPrefix + LONG;
         }else if(componentType == char.class){
            type = arrayPrefix + CHAR;
         }else if(componentType == byte.class){
            type = arrayPrefix + BYTE;
         }else if(componentType == short.class){
            type = arrayPrefix + SHORT;
         }else if(componentType == void.class){
            type = arrayPrefix + VOID;
         }else if(componentType == boolean.class){
            type = arrayPrefix + BOOLEAN;
         }else{
            // its an object or an array of objects
            type = arrayPrefix + CLASS_START + dotClassNameToSlashClassName(_clazz.getName()) + CLASS_END;
         }

      }



       String getType(){
         return (type);
      }

      boolean isVoid(){
         return (type.charAt(0) == VOID);
      }

      boolean isInt(){
         return (type.charAt(0) == INT);
      }

      boolean isLong(){
         return (type.charAt(0) == LONG);
      }

      boolean isShort(){
         return (type.charAt(0) == SHORT);
      }

      boolean isBoolean(){
         return (type.charAt(0) == BOOLEAN);
      }

      boolean isChar(){
         return (type.charAt(0) == CHAR);
      }

      boolean isFloat(){
         return (type.charAt(0) == FLOAT);
      }

      boolean isDouble(){
         return (type.charAt(0) == DOUBLE);
      }

      boolean isByte(){
         return (type.charAt(0) == BYTE);
      }

      boolean isObject(){
         return (type.charAt(0) == CLASS_START);
      }

      String getObjectClassName(){
         return (TypeHelper.signatureToDotClassName(type, 0));
      }

      String getMangledClassName(){
         return (TypeHelper.signatureToMangledClassName(type, 0));
      }

      private String type;

      final boolean isArray(){
         return (arrayDimensions > 0);
      }

      final int getArrayDimensions(){
         return (arrayDimensions);
      }

      final boolean isArrayOfObjects(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isObject());
      }

      final boolean isArrayOfInts(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isInt());
      }

      final boolean isArrayOfFloats(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isFloat());
      }

      final boolean isArrayOfDoubles(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isDouble());
      }

      final boolean isArrayOfChars(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isChar());
      }

      final boolean isArrayOfLong(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isLong());
      }

      final boolean isArrayOfShorts(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isShort());
      }

      final boolean isArrayOfBytes(int _dim){
         return (isArray() && getArrayDimensions() == _dim && isByte());
      }

      final boolean isPrimitive(){
         return (isInt() || isFloat() || isDouble() || isChar() || isLong() || isShort() || isByte());
      }

      String primitiveCharToJavaName(char _ch){
         switch(_ch){
            case VOID:
               return ("void");
            case DOUBLE:
               return ("double");
            case FLOAT:
               return ("float");
            case INT:
               return ("int");
            case CHAR:
               return ("char");
            case BYTE:
               return ("byte");
            case SHORT:
               return ("short");
            case LONG:
               return ("long");
            case BOOLEAN:
               return ("boolean");
         }
         return ("?");
      }

      String getJavaName(){
         String javaName = "?";
         if(isPrimitive() || isVoid()){
            javaName = primitiveCharToJavaName(type.charAt(0));
         }else if(isObject()){
            javaName = getObjectClassName();
         }
         return (javaName);
      }

      public boolean matches(Class<?> _type){
         String javaName = getJavaName();
         return (_type.getName().equals(javaName));
      }

      @Override public String toString(){
           StringBuilder sb = new StringBuilder(getJavaName());
           for (int i=0; i<arrayDimensions; i++){
              sb.append("[]");
           }
           return(sb.toString());
      }
   }

   public static class Arg extends Type{
      Arg(String _signature, int _start, int _pos, int _argc){
         super(_signature.substring(_start, _pos + 1));
         argc = _argc;
      }

      Arg(Class _clazz, int _argc){
         super(_clazz);
         argc = _argc;
      }

      private int argc;

      int getArgc(){
         return (argc);
      }
   }

   public static class MethodInfo{
      ArgsAndReturnType argsAndReturnType;
      Type containingClass;
      String methodName;

      public MethodInfo(Method _method){
         argsAndReturnType = new ArgsAndReturnType(_method);
         containingClass = new Type(_method.getDeclaringClass());
         methodName = _method.getName();
      }

      public MethodInfo(ClassModel.ConstantPool.MethodEntry _methodEntry){
         argsAndReturnType = _methodEntry.getArgsAndReturnType();
         containingClass = _methodEntry.getContainingClass();
         methodName = _methodEntry.getName();

      }

      public boolean equals(MethodInfo _other){
         return (_other.methodName.equals(methodName) && _other.containingClass.equals(containingClass) && _other.argsAndReturnType.equals(argsAndReturnType));
      }

   }

   public static class FieldInfo{
      Type type;
      Type containingClass;
      String fieldName;

      FieldInfo(Field _field){
         type = new Type(_field);
         containingClass = new Type(_field.getDeclaringClass());
         fieldName = _field.getName();
      }

      FieldInfo(ClassModel.ConstantPool.FieldEntry _fieldEntry){
         type = _fieldEntry.getType();
         containingClass = _fieldEntry.getContainingClass();
         fieldName = _fieldEntry.getName();
      }

      public boolean equals(FieldInfo _other){
         return (_other.fieldName.equals(fieldName) && _other.containingClass.equals(containingClass) && _other.type.equals(type));
      }
   }

   public static class ArgsAndReturnType{
      private static enum SignatureParseState{
         skipping,
         inArgs,
         inClass,
         inArray,
         done;
      }

      ;


      Arg[] args;
      Type returnType;

      public Arg[] getArgs(){
         return (args);
      }

      public Type getReturnType(){
         return (returnType);
      }


      public ArgsAndReturnType(String _signature){


         SignatureParseState state = SignatureParseState.skipping;
         List<Arg> argList = new ArrayList<Arg>();
         int start = 0;

         for(int pos = 0; state != SignatureParseState.done; pos++){
            char ch = _signature.charAt(pos);
            switch(ch){
               case ARG_START:
                  state = SignatureParseState.inArgs;
                  break;
               case ARG_END:
                  state = SignatureParseState.done;
                  returnType = new Type(_signature.substring(pos + 1));
                  break;
               case ARRAY_DIM:
                  switch(state){
                     case inArgs:
                        state = SignatureParseState.inArray;
                        start = pos;
                        break;

                  }
                  // we don't care about arrays
                  break;
               case CLASS_START:
                  // beginning of Ljava/lang/String; or something
                  switch(state){
                     case inArgs:
                        start = pos;
                        state = SignatureParseState.inClass;
                        break;
                     case inArray:
                        state = SignatureParseState.inClass;
                        break;
                  }
                  break;
               case CLASS_END:
                  argList.add(new Arg(_signature, start, pos, argList.size()));
                  state = SignatureParseState.inArgs;
                  break;
               default:
                  // we have IJBZDF so inc counter if we are still inArgs
                  switch(state){
                     case inArgs:
                        start = pos;
                        argList.add(new Arg(_signature, start, pos, argList.size()));
                        state = SignatureParseState.inArgs;
                        break;
                     case inArray:
                        argList.add(new Arg(_signature, start, pos, argList.size()));
                        state = SignatureParseState.inArgs;
                        break;

                  }
                  break;
            }

         }
          System.out.println("method signature of "+_signature+" = "+returnType+" method( "+argList+")");

         args = argList.toArray(new Arg[0]);
      }

      public ArgsAndReturnType(Method _method){
         args = new Arg[_method.getParameterCount()];
         Class<?> argsAsClasses[] = _method.getParameterTypes();
         for(int i = 0; i < argsAsClasses.length; i++){
            args[i] = new Arg(argsAsClasses[i], i);
         }
         returnType = new Type(_method.getReturnType());
      }

      public boolean matches(Method _method){
         return (returnType.matches(_method.getReturnType()));
      }

   }

}