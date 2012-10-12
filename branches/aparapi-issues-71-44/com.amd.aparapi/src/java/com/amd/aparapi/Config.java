/*
Copyright (c) 2010-2011, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following
disclaimer. 

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
disclaimer in the documentation and/or other materials provided with the distribution. 

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

If you use the software (in whole or in part), you shall adhere to all applicable U.S., European, and other export
laws, including but not limited to the U.S. Export Administration Regulations ("EAR"), (15 C.F.R. Sections 730 through
774), and E.U. Council Regulation (EC) No 1334/2000 of 22 June 2000.  Further, pursuant to Section 740.6 of the EAR,
you hereby certify that, except pursuant to a license granted by the United States Department of Commerce Bureau of 
Industry and Security or as otherwise permitted pursuant to a License Exception under the U.S. Export Administration 
Regulations ("EAR"), you will not (1) export, re-export or release to a national of a country in Country Groups D:1,
E:1 or E:2 any restricted technology, software, or source code you receive hereunder, or (2) export to Country Groups
D:1, E:1 or E:2 the direct product of such technology or software, if such foreign produced direct product is subject
to national security controls as identified on the Commerce Control List (currently found in Supplement 1 to Part 774
of EAR).  For the most current Country Group listings, or for additional information about the EAR or your obligations
under those regulations, please refer to the U.S. Bureau of Industry and Security's website at http://www.bis.doc.gov/. 

 */
package com.amd.aparapi;

import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.amd.aparapi.instruction.Instruction;
import com.amd.aparapi.jni.ConfigJNI;
import com.amd.aparapi.print.InstructionViewer;

/**
 * A central location for holding all runtime configurable properties as well as logging configuration.
 * 
 * Ideally we will find all properties used by <code>Aparapi</code> here. Please consider updating this class if you wish
 * to add new properties which control <code>Aparapi</code>s behavior.
 * 
 * @author gfrost
 * 
 */
public class Config {

   private static final String propPkgName = Config.class.getPackage().getName();

   // Logging setup
   private static final String logPropName = propPkgName + ".logLevel";

   private static Logger logger = Logger.getLogger(Config.getLoggerName());

   private static ConfigJNI configJNI = new ConfigJNI(propPkgName);

   private static final Config instance = new Config();

   public static InstructionListener instructionListener = null;

   static {
      try {
         final Level level = Level.parse(System.getProperty(getLoggerName(), "WARNING"));

         final Handler[] handlers = Logger.getLogger("").getHandlers();
         for (final Handler handler : handlers) {
            handler.setLevel(level);
         }

         logger.setLevel(level);

      } catch (final Exception e) {
         System.out.println("Exception " + e + " in Aparapi logging setup.");
         e.printStackTrace();
      }
   }

   static {
      if (configJNI.isEnableInstructionDecodeViewer() && ((configJNI.getInstructionListenerClassName() == null) || configJNI.getInstructionListenerClassName().equals(""))) {
         configJNI.setInstructionListenerClassName(InstructionViewer.class.getName());
      }

      if ((configJNI.getInstructionListenerClassName() != null) && !configJNI.getInstructionListenerClassName().equals("")) {
         try {
            final Class<?> instructionListenerClass = Class.forName(configJNI.getInstructionListenerClassName());
            instructionListener = (InstructionListener) instructionListenerClass.newInstance();
         } catch (final ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
         } catch (final InstantiationException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
         } catch (final IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
         }
      }

      if (configJNI.isDumpFlags()) {
         System.out.println(propPkgName + ".executionMode{GPU|CPU|JTP|SEQ}=" + configJNI.getExecutionMode());
         System.out.println(propPkgName + ".logLevel{OFF|FINEST|FINER|FINE|WARNING|SEVERE|ALL}=" + logger.getLevel());
         System.out.println(propPkgName + ".enableProfiling{true|false}=" + configJNI.isEnableProfiling());
         System.out.println(propPkgName + ".enableProfilingCSV{true|false}=" + configJNI.isEnableProfilingCSV());
         System.out.println(propPkgName + ".enableVerboseJNI{true|false}=" + configJNI.isEnableVerboseJNI());
         System.out.println(propPkgName + ".enableVerboseJNIOpenCLResourceTracking{true|false}=" + configJNI.isEnableVerboseJNIOpenCLResourceTracking());
         System.out.println(propPkgName + ".enableShowGeneratedOpenCL{true|false}=" + configJNI.isEnableShowGeneratedOpenCL());
         System.out.println(propPkgName + ".enableExecutionModeReporting{true|false}=" + configJNI.isEnableExecutionModeReporting());
         System.out.println(propPkgName + ".enableInstructionDecodeViewer{true|false}=" + configJNI.isEnableInstructionDecodeViewer());
         System.out.println(propPkgName + ".instructionListenerClassName{<class name which extends com.amd.aparapi.Config.InstructionListener>}=" + configJNI.getInstructionListenerClassName());
      }
   }

   /**
    * Private singleton default constructor
    */
   private Config() {

   }

   /**
    * Returns the singleton instance of Config
    * 
    * @return Singleton instance of Config
    */
   public static Config getInstance() {
      return instance;
   }

   public interface InstructionListener {
      public void showAndTell(String message, Instruction _start, Instruction _instruction);
   }

   /**
    * Retrieves the currently configured Logger Name
    * 
    * @return
    *    The currently configured Logger Name
    */
   public static String getLoggerName() {
      return logPropName;
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isDisableUnsafe() {
      return configJNI.isDisableUnsafe();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return String
    */
   public static String getExecutionMode() {
      return configJNI.getExecutionMode();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableExecutionModeReporting() {
      return configJNI.isEnableExecutionModeReporting();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableShowGeneratedOpenCL() {
      return configJNI.isEnableShowGeneratedOpenCL();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isVerboseComparitor() {
      return configJNI.isVerboseComparitor();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnablePUTFIELD() {
      return configJNI.isEnablePUTFIELD();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableARETURN() {
      return configJNI.isEnableARETURN();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnablePUTSTATIC() {
      return configJNI.isEnablePUTSTATIC();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableINVOKEINTERFACE() {
      return configJNI.isEnableINVOKEINTERFACE();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableGETSTATIC() {
      return configJNI.isEnableGETSTATIC();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableATHROW() {
      return configJNI.isEnableATHROW();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableMONITOR() {
      return configJNI.isEnableMONITOR();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableNEW() {
      return configJNI.isEnableNEW();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableSWITCH() {
      return configJNI.isEnableSWITCH();
   }

   /**
    * A pass-through method for JNI property accessor
    * 
    * @return boolean
    */
   public static boolean isEnableMETHODARRAYPASSING() {
      return configJNI.isEnableMETHODARRAYPASSING();
   }
}
