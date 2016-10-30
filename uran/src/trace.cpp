/*
 * trace.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: nullifiedcat
 */

#include "trace.h"

#include <cstdint>

#include "fixsdk.h"
#include <client_class.h>
#include <icliententity.h>


trace::FilterDefault::FilterDefault() {
	m_pSelf = nullptr;
}

trace::FilterDefault::~FilterDefault() {};

void trace::FilterDefault::SetSelf(IClientEntity* self) {
	m_pSelf = self;
}

bool trace::FilterDefault::ShouldHitEntity(IHandleEntity* handle, int mask) {
	IClientEntity* entity = (IClientEntity*) handle;
	ClientClass* clazz = entity->GetClientClass();
	/* Ignore invisible entities that we don't wanna hit */
	switch(clazz->m_ClassID) {
	// TODO magic numbers: invisible entity ids
	case 64:
	case 225:
	case 55:
		return false;
	}
	/* Do not hit yourself. Idiot. */
	if (entity == m_pSelf) return false;
	return true;
}

TraceType_t trace::FilterDefault::GetTraceType() const {
	return TRACE_EVERYTHING;
}