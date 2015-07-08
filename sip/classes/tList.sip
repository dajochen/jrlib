template<TYPE *>
%MappedType tList<TYPE*>
{
%TypeHeaderCode
// Include the library interface to the type being mapped.
#include <../classes/tList.h>
%End

%ConvertToTypeCode
    // See if we are just being asked to check the type of the Python
    // object.
    if (sipIsErr == NULL)
    {
        // Check it is a list.
        if (!PyList_Check(sipPy))
            return 0;

        // Now check each element of the list is of the type we expect.
        // The template is for a pointer type so we don't disallow None.
        for (int i = 0; i < PyList_GET_SIZE(sipPy); ++i)
            if (!sipCanConvertToType(PyList_GET_ITEM(sipPy, i), sipType_TYPE, 0))
                return 0;

        return 1;
    }

    // Create the instance on the heap.
    tList<TYPE *> *ql = new tList<TYPE *>;

    for (int i = 0; i < PyList_GET_SIZE(sipPy); ++i)
    {
        // Use the SIP API to convert the Python object to the
        // corresponding C++ instance.  Note that we apply any ownership
        // transfer to the list itself, not the individual elements.
        TYPE *t = reinterpret_cast<TYPE *>(sipConvertToType(
                                            PyList_GET_ITEM(sipPy, i),
                                            sipType_TYPE, 0, 0, 0,
                                            sipIsErr));

        if (*sipIsErr)
        {
            // Tidy up.
            delete ql;

            // There is nothing on the heap.
            return 0;
        }

        // Add the pointer to the C++ instance.
        ql->append(t);
    }

    // Return the instance on the heap.
    *sipCppPtr = ql;

    // Apply the normal transfer.
    return sipGetState(sipTransferObj);
%End

%ConvertFromTypeCode
    PyObject *l;

    // Create the Python list of the correct length.
    if ((l = PyList_New(sipCpp->count())) == NULL)
        return NULL;

    // Go through each element in the C++ instance and convert it to the
    // corresponding Python object.
    for (int i = 0; i < sipCpp->count(); ++i)
    {
        TYPE *t = sipCpp->at(i);
        PyObject *tobj;

        if ((tobj = sipConvertFromType(t, sipType_TYPE, sipTransferObj)) == NULL)
        {
            // There was an error so garbage collect the Python list.
            Py_DECREF(l);
            return NULL;
        }

        PyList_SET_ITEM(l, i, tobj);
    }

    // Return the Python list.
    return l;
%End
};
