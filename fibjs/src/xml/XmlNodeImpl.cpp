/*
 * XmlNodeImpl.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: lion
 */

#include "object.h"
#include "XmlNodeImpl.h"
#include "XmlDocument.h"
#include "XmlDocumentType.h"
#include "XmlElement.h"
#include "XmlText.h"
#include "XmlComment.h"
#include "XmlCDATASection.h"
#include "XmlProcessingInstruction.h"

namespace fibjs {

const char* XmlNodeImpl::s_nss[][2] = {
    { "xml", "http://www.w3.org/XML/1998/namespace" },
    { "xmlns", "http://www.w3.org/2000/xmlns/" },
    { NULL, NULL }
};

XmlNodeImpl* XmlNodeImpl::fromNode(XmlNode_base* pNode)
{
    int32_t type;

    pNode->get_nodeType(type);

    switch (type) {
    case xml_base::C_ELEMENT_NODE:
        return (XmlElement*)pNode;
    case xml_base::C_TEXT_NODE:
        return (XmlText*)pNode;
    case xml_base::C_CDATA_SECTION_NODE:
        return (XmlCDATASection*)pNode;
    case xml_base::C_PROCESSING_INSTRUCTION_NODE:
        return (XmlProcessingInstruction*)pNode;
    case xml_base::C_COMMENT_NODE:
        return (XmlComment*)pNode;
    case xml_base::C_DOCUMENT_NODE:
        return (XmlDocument*)pNode;
    case xml_base::C_DOCUMENT_TYPE_NODE:
        return (XmlDocumentType*)pNode;
    }

    return NULL;
}
}
