
#ifndef SIGNATURE_F_TYPE_H
#define SIGNATURE_F_TYPE_H

#include "PDBFeatureType.h"
#include <string>

// stores a vector in a sparse format
class SignatureFeatureType : public PDBFeatureType {

public:

	// constructors
    SignatureFeatureType() = default;
    SignatureFeatureType(const std::string& boc,
                         const std::string& returnType,
                         const std::string& methodName,
                         const std::string& parameters);

    // get methods
    const std::string& getBOC();
    const std::string& getReturnType();
    const std::string& getMethodName();
    const std::string& getParameters();

	// from the interface
	const std::string &getTypeName () override;
	int getCode () override;
	void *serialize (void *toHere, size_t &size) override;
	void *deSerialize (void *fromHere, size_t &size) override;
	PDBFeatureTypePtr getNewFeatureTypeObject () override;
	std::string display () override;
	
private:
	
    std::string boc_;
	std::string returnType_;
	std::string methodName_;
	std::string parameters_;
};

#endif
