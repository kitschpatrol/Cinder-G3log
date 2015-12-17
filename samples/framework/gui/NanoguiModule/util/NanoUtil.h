// This header file was auto-generated by ClassMate++
// Created: 28 Oct 2015 7:00:35 pm
// Copyright (c) 2015, HurleyWorks

#pragma once


struct NanoUtil
{
      NanoUtil()
      {
         timer.start();
      }

      static std::vector<std::pair<int, std::string>> loadImageDirectory (NVGcontext * ctx, const std::string & folder);

      static double getElapsedSeconds()
      {
         return timer.getSeconds();
      }

   private:
      static cinder::Timer timer;
}; // end class NanoUtil
