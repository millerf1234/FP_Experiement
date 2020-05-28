
// 
// This code is a way-overkill demonstration meant for 
// comparing negative and positive 0 in floating point. 
//
// WHAT I LEARNED:  It seems as though things are exactly as I expected.
//                    [I originally had a much more interesting statement written 
//                     here discussing the quite surprising/unexpected differences 
//                     with the behaviors between -0.0 and 0.0 when working with 32-bit 
//                     floats versus 64-bit doubles. Alas, it unfortunately turned out 
//                     that I had a bug and there really is not much difference between 
//                     how floats and doubles work]

//
// Future Work:     It would be really easy to add checks for how floats and doubles differ
//                  with representing the values of infinity/NAN. Could be added with probably
//                  as little as 3 more lines of code each (slightly more lines would be required
//                  to match the output format announcing each existing test). 
//

// Programmer:  Forrest Miller
// Date:        May 27, 2020 


// Note:   Please forgive my occasional lack of formality when naming my custom types/variables/etc...
//         Also please excuse my wide-spread usage of magic numbers and possible violation of common programming
//             norms. [Hey at least I refrained from using 'goto' anywhere in this project] 

#ifndef FP_EXPERIMENT_H_
#define FP_EXPERIMENT_H_ 

#include <cassert>
#include <cinttypes>
#include <cfloat>
#include <cctype> //preferred over <ctype.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iomanip>

//Customize what data is compared with 'operator==()'
// (Must define at least one)
#define RUN_FLOAT_COMPARISON
#define RUN_DOUBLE_COMPARISON
#define RUN_BYTE_COMPARISON


typedef union PUN_INTENDED {
    float val;
    double valD;
    std::byte valBytes[8];
    PUN_INTENDED() {
        valBytes[0] = std::byte(0);
        valBytes[1] = std::byte(0);
        valBytes[2] = std::byte(0);
        valBytes[3] = std::byte(0);
        valBytes[4] = std::byte(0);
        valBytes[5] = std::byte(0);
        valBytes[6] = std::byte(0);
        valBytes[7] = std::byte(0);
    }
    explicit PUN_INTENDED(const float& v) : PUN_INTENDED() {
        fprintf(stdout, "\nCalled with float!\n");
        val = v;
    }
    PUN_INTENDED(const double& vd) : PUN_INTENDED() {
        fprintf(stdout, "\nCalled with double!\n");
        valD = vd;
    }

    void printSelf() const noexcept {
        //printf("Printing Punned Data: \n");
        printf("  float val: %f", val);
        printf("   Bytes: 0x");
        //const auto oldWidth = std::cout.width(2);
        //const auto oldFill = std::cout.fill('0');
        std::cout << std::hex << std::internal << std::setw(2) << std::setfill('0') << std::to_integer<int>(valBytes[0]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[1]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[2]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[3]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[4]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[5]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[6]) << ", 0x";
        std::cout << std::hex << std::to_integer<int>(valBytes[7]) << "\n";
        //std::cout.fill(oldFill);
        //std::cout.width(oldWidth);
        printf(" [double val: %f]\n", valD);

    }

    bool operator==(const PUN_INTENDED& that) const noexcept {
        bool res = true; //Values will be assumed to be equal until proven otherwise

        //Print Header
        printf("\n");
        printDelimiter(79, '~', true);
        printDelimiter(79, '+', true);
        printDelimiter(79, '~', true);
        printf("'Operator==()' called on two FloatBytePuns!\n");

        //Check identity case
        if (this == &that) {
            printf("\n\n\nATTENTION: Identity Case Detected By Comparison Operator!\n"
                   "   ->Well of course this union object will be equal to\n"
                   "   ->itself, what are you trying to pull here?!?!\n\n\n");
            printf("[LHand    and    RHand]\n");
            printSelf();
        }
        else {
        //Print Union Contents
            printf("                                                             [ L-Hand Value ]\n");
            printSelf();
            printf("\n                                                             [ R-Hand Value ]\n");
            that.printSelf();

            //Print delimiter between header and results
            printf("\n");
            printDelimiter(10, ' ', false);
            printDelimiter(50, '*', true);

#ifdef RUN_FLOAT_COMPARISON
            printf("\n    Comparing Float Data.......");
            if (val == that.val)
                printf("Equal!\n");
            else {
                printf("NOT Equal!\n");
                res = false;
            }
#else 
            printf("\n    Skipping Float Comparison\n");
#endif //RUN_FLOAT_COMPARISON

#ifdef RUN_DOUBLE_COMPARISON
            printf("\n    Comparing Double Data......");
            if (valD == that.valD)
                printf("Equal!\n");
            else {
                printf("NOT equal!\n");
                res = false;
            }
#else 
            printf("\n    Skipping Double Comparison\n");
#endif //RUN_DOUBLE_COMPARISON

#ifdef RUN_BYTE_COMPARISON
            printf("\n    Comparing BYTE Data........");
            if (valBytes[0] == that.valBytes[0])
                printf("[0] is Equal!\n");
            else {
                printf("[0] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[1] == that.valBytes[1])
                printf("[1] is Equal!\n");
            else {
                printf("[1] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[2] == that.valBytes[2])
                printf("[2] is Equal!\n");
            else {
                printf("[2] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[3] == that.valBytes[3])
                printf("[3] is Equal!\n");
            else {
                printf("[3] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[4] == that.valBytes[4])
                printf("[4] is Equal!\n");
            else {
                printf("[4] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[5] == that.valBytes[5])
                printf("[5] is Equal!\n");
            else {
                printf("[5] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[6] == that.valBytes[6])
                printf("[6] is Equal!\n");
            else {
                printf("[6] is NOT Equal!\n");
                res = false;
            }
            printDelimiter(23, ' ', false);
            printDelimiter(8, '.', false);
            if (valBytes[7] == that.valBytes[7])
                printf("[7] is Equal!");
            else {
                printf("[7] is NOT Equal!");
                res = false;
            }
#else 
            printf("\n    Skipping Byte Comparison");
#endif //RUN_DOUBLE_COMPARISON
        }
        //Print Ending Delimiter
        printf("\n");
        printDelimiter(79, '~', true);
        printDelimiter(79, '=', true);
        printDelimiter(79, '~', true);
        printf("\n");
        return res;
    }

private: //Helper function
    void printDelimiter(uint64_t width, char c, bool addNewLine) const noexcept {
        for (uint64_t i = 0ULL; i < width; i++)
            printf("%c", c);
        if (addNewLine)
            printf("\n");
    }
} FloatBytePun;





inline void performFPTest() noexcept {
    fprintf(stdout, "\nFirst here is a reality-check on the size of each data type:\n");
    const uint64_t sizeOfFloat = sizeof(float);
    printf("\tSize of float.......%" PRIu64 "\n", sizeOfFloat);
    assert(sizeOfFloat == 4ULL);
    const uint64_t sizeOfDouble = sizeof(double);
    printf("\tSize of double......%" PRIu64 "\n", sizeOfDouble);
    assert(sizeOfDouble == 8ULL);
    const uint64_t sizeOfByte = sizeof(std::byte);
    printf("\tSize of std::byte:..%" PRIu64 "\n", sizeOfByte);
    assert(sizeOfDouble == 8ULL);


    printf("\n\n\n\n");
    printf("                              +---------------+\n");
    printf("                              | All Bits Zero |\n");
    printf("                              +---------------+");
    FloatBytePun zero1, zero2;
    const bool allBitsZero = static_cast<bool>(zero1 == zero2);
    fprintf(stdout, "AllBitsZero returned:   %s\n\n\n", allBitsZero ? "TRUE" : "FALSE");

    printf("\n\n\n\n");
    printf("                             +-----------------+\n");
    printf("                             | Float  +/- Zero |\n");
    printf("                             +-----------------+");
    FloatBytePun neg;
    neg.val = -0.0f;
    FloatBytePun pos;
    pos.val = 0.0f;
    const bool floatZero = static_cast<bool>(neg == pos);
    fprintf(stdout, "FloatZero returned:   %s\n\n\n", floatZero ? "TRUE" : "FALSE");

    printf("\n\n\n\n");
    printf("                             +-----------------+\n");
    printf("                             | Double +/- Zero |\n");
    printf("                             +-----------------+");
    neg.valD = -0.0;
    pos.valD = 0.0;

    const bool doubleZero = static_cast<bool>(neg == pos);
    fprintf(stdout, "DoubleZero returned:   %s\n\n\n", doubleZero ? "TRUE" : "FALSE");

    return;
}


//Check to make sure at least one comparison operation is taking place
#if (!(defined RUN_FLOAT_COMPARISON)  &&  \
     !(defined RUN_DOUBLE_COMPARISON) &&  \
     !(defined RUN_BYTE_COMPARISON))
#error "Must have at least one comparison [FLOAT, DOUBLE or BYTE] enabled!\n"
#endif




//Report configuration of this file as part of compiling
#pragma message ("~\n~\n~\n~\n~\n~\n")
#pragma message (" *****************************************************************************\n")
#pragma message (" ******                                                                 ******\n")
#pragma message (" ******               #################################                 ******\n")
#pragma message (" ******               #  FP_Experiment Configuration  #                 ******\n")
#pragma message (" ******               #################################                 ******\n")
#pragma message (" ******                                                                 ******\n")
#pragma message (" ******  Behavior of \"FloatBytePun::Operator==()\"                       ******\n")
#ifdef RUN_FLOAT_COMPARISON
#pragma message (" ******         Float Comparison:    ENABLED                            ******\n")
#else 
#pragma message (" ******         Float Comparison:    DISABLED                           ******\n")
#endif 
#ifdef RUN_DOUBLE_COMPARISON
#pragma message (" ******         Double Comparison:   ENABLED                            ******\n")
#else 
#pragma message (" ******         Double Comparison:   DISABLED                           ******\n")
#endif 
#ifdef RUN_BYTE_COMPARISON
#pragma message (" ******         Byte Comparison:     ENABLED                            ******\n")
#else 
#pragma message (" ******         Byte Comparison:     DISABLED                           ******\n")
#endif 
#pragma message (" ******                                                                 ******\n")
#pragma message (" ******                ################################                 ******\n")
#pragma message (" ******                ##    End of Configuration    ##                 ******\n")
#pragma message (" ******                ################################                 ******\n")
#pragma message (" ******                                                                 ******\n")
#pragma message (" *****************************************************************************\n")
#pragma message ("~\n~\n~\n~\n~\n~\n~\n")




//Undefined file-local macros to avoid namespace pollution
#ifdef RUN_FLOAT_COMPARISON
#undef RUN_FLOAT_COMPARISON
#endif 
#ifdef RUN_DOUBLE_COMPARISON
#undef RUN_DOUBLE_COMPARISON
#endif 
#ifdef RUN_BYTE_COMPARISON
#undef RUN_BYTE_COMPARISON
#endif 


#endif //FP_EXPERIMENT_H_
