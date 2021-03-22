/*
 * fibjs.h
 *
 *  Created on: May 28, 2018
 *      Author: lion
 */

#include "utils.h"

#ifndef _FIBJS_H_
#define _FIBJS_H_

namespace fibjs {

void runGuiThread(int argc, char* argv[]);
void startJavascriptApp(int32_t argc, char** argv, result_t (*main)(Isolate*));
result_t FiberProcJsEntry(Isolate* isolate);

} /* namespace fibjs */
#endif /* FIBER_H_ */
