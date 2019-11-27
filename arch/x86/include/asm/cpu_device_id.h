/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _CPU_DEVICE_ID
#define _CPU_DEVICE_ID 1

/*
 * Declare drivers belonging to specific x86 CPUs
 * Similar in spirit to pci_device_id and related PCI functions
 */

#include <linux/mod_devicetable.h>

#define X86_STEPPINGS(mins, maxs)    GENMASK(maxs, mins)

/**
 * X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE - Base macro for CPU matching
 * @_vendor:	The vendor name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@_vendor
 * @_family:	The family number or X86_FAMILY_ANY
 * @_model:	The model number, model constant or X86_MODEL_ANY
 * @_steppings:	Bitmask for steppings, stepping constant or X86_STEPPING_ANY
 * @_feature:	A X86_FEATURE bit or X86_FEATURE_ANY
 * @_data:	Driver specific data or NULL. The internal storage
 *		format is unsigned long. The supplied value, pointer
 *		etc. is casted to unsigned long internally.
 *
 * Backport version to keep the SRBDS pile consistant. No shorter variants
 * required for this.
 */
#define X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE(_vendor, _family, _model, \
						    _steppings, _feature, _data) { \
	.vendor		= X86_VENDOR_##_vendor,				\
	.family		= _family,					\
	.model		= _model,					\
	.steppings	= _steppings,					\
	.feature	= _feature,					\
	.driver_data	= (unsigned long) _data				\
}

extern const struct x86_cpu_id *x86_match_cpu(const struct x86_cpu_id *match);

/*
 * Match specific microcode revisions.
 *
 * vendor/family/model/stepping must be all set.
 *
 * Only checks against the boot CPU.  When mixed-stepping configs are
 * valid for a CPU model, add a quirk for every valid stepping and
 * do the fine-tuning in the quirk handler.
 */

struct x86_cpu_desc {
	__u8	x86_family;
	__u8	x86_vendor;
	__u8	x86_model;
	__u8	x86_stepping;
	__u32	x86_microcode_rev;
};

#define INTEL_CPU_DESC(mod, step, rev) {			\
	.x86_family = 6,					\
	.x86_vendor = X86_VENDOR_INTEL,				\
	.x86_model = mod,					\
	.x86_stepping = step,					\
	.x86_microcode_rev = rev,				\
}

extern bool x86_cpu_has_min_microcode_rev(const struct x86_cpu_desc *table);

#endif
