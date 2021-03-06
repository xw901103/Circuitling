/**
 * Circuitling
 * 
 * Copyright (c) 2013, Circuitling Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies, 
 * either expressed or implied, of the Circuitling Project.
 * 
 * authors:Xu Waycell [xw901103@gmail.com]
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#if !defined(BEGIN_NAMESPACE) && !defined(END_NAMESPACE)
#define BEGIN_NAMESPACE namespace Circuitling{
#define END_NAMESPACE };
#endif

#if !defined(DISABLE_COPY)
#define DISABLE_COPY(CLASS)\
private:\
    CLASS& operator= (const CLASS&);
#endif

BEGIN_NAMESPACE

enum ToolType {
    UnknowType,
    Cursor,
    Element
};

enum ToolItem {
    UnknowItem,
    //cursor
    SelectCursor,
    ConnectCursor,
    MoveCursor,
    ZoomCursor,
    //element
    NodeElement, // will be removed
    ResistorElement,
    CapacitorElement,
    InductorElement,
    DiodeElement,
    DC_VoltageSourceElement,
    AC_VoltageSourceElement,
};

enum ElementType {
    CustomizedElement,
    Node, // will be removed
    DC_VoltageSource,
    AC_VoltageSource,
    Resistor,
    VolatageSource,
    CurrentSource,
    Capacitor,
    Inductor,
    Diode
};

END_NAMESPACE

#endif
