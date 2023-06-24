
#include "CurrencyConverter.h"

CurrencyConverter::CurrencyConverter(){
    setCurrencySymbols();
//    setConversionRates();
}

void CurrencyConverter::setConversionRate(const std::string &fromCurrency, const std::string &toCurrency, double rate){
    std::string key = generateKey(fromCurrency, toCurrency);
    m_conversionRates[key] = rate;
}

double CurrencyConverter::convert(const std::string &fromCurrency, const std::string &toCurrency, double amount){
    std::string key = fromCurrency + toCurrency;
    auto it = m_conversionRates.find(key);
    if (it != m_conversionRates.end()) {
        return amount * it->second;
    }
    else {
        std::cout << "Conversion rate not found for " << fromCurrency << " to " << toCurrency << std::endl;
        return 0.0;
    }
}

void CurrencyConverter::setCurrencySymbols(){
    m_currencySymbols["USD"] = "$";    // United States Dollar
    m_currencySymbols["AED"] = "د.إ";  // UAE Dirham
    m_currencySymbols["AUD"] = "$";    // Australian Dollar
    m_currencySymbols["BRL"] = "R$";   // Brazilian Real
    m_currencySymbols["CAD"] = "$";    // Canadian Dollar
    m_currencySymbols["CHF"] = "CHF";  // Swiss Franc
    m_currencySymbols["CNY"] = "¥";    // Chinese Yuan
    m_currencySymbols["EGP"] = "£";    // Egyptian Pound
    m_currencySymbols["EUR"] = "€";    // Euro
    m_currencySymbols["GBP"] = "£";    // British Pound
    m_currencySymbols["HKD"] = "$";    // Hong Kong Dollar
    m_currencySymbols["INR"] = "₹";    // Indian Rupee
    m_currencySymbols["IRR"] = "﷼";    // Iranian Rial
    m_currencySymbols["JPY"] = "¥";    // Japanese Yen
    m_currencySymbols["KRW"] = "₩";    // South Korean Won
    m_currencySymbols["MXN"] = "$";    // Mexican Peso
    m_currencySymbols["NOK"] = "kr";   // Norwegian Krone
    m_currencySymbols["NZD"] = "$";    // New Zealand Dollar
    m_currencySymbols["PLN"] = "zł";   // Polish Zloty
    m_currencySymbols["RUB"] = "₽";    // Russian Ruble
    m_currencySymbols["SAR"] = "﷼";    // Saudi Riyal
    m_currencySymbols["SEK"] = "kr";   // Swedish Krona
    m_currencySymbols["TRY"] = "₺";    // Turkish Lira
    m_currencySymbols["ZAR"] = "R";    // South African Rand
}

void CurrencyConverter::setConversionRates(){
    setAEDConversionRates();
    setAUDConversionRates();
    setBRLConversionRates();
    setCADConversionRates();
    setCHFConversionRates();
    setCNYConversionRates();
    setEGPConversionRates();
    setEURConversionRates();
    setGBPConversionRates();
    setHKDConversionRates();
    setINRConversionRates();
    setIRRConversionRates();
    setJPYConversionRates();
    setKRWConversionRates();
    setMXNConversionRates();
    setNOKConversionRates();
    setNZDConversionRates();
    setPLNConversionRates();
    setRUBConversionRates();
    setSARConversionRates();
    setSEKConversionRates();
    setTRYConversionRates();
    setUSDConversionRates();
    setZARConversionRates();
}

void CurrencyConverter::setAEDConversionRates(){
    setConversionRate("AED", "USD", 0.27);    // UAE Dirham to USD
    setConversionRate("AED", "AUD", 0.37);    // UAE Dirham to Australian Dollar
    setConversionRate("AED", "BRL", 1.45);    // UAE Dirham to Brazilian Real
    setConversionRate("AED", "CAD", 0.34);    // UAE Dirham to Canadian Dollar
    setConversionRate("AED", "CHF", 0.25);    // UAE Dirham to Swiss Franc
    setConversionRate("AED", "CNY", 1.78);    // UAE Dirham to Chinese Yuan
    setConversionRate("AED", "EGP", 4.31);    // UAE Dirham to Egyptian Pound
    setConversionRate("AED", "EUR", 0.23);    // UAE Dirham to Euro
    setConversionRate("AED", "GBP", 0.20);    // UAE Dirham to British Pound
    setConversionRate("AED", "HKD", 2.18);    // UAE Dirham to Hong Kong Dollar
    setConversionRate("AED", "INR", 21.28);   // UAE Dirham to Indian Rupee
    setConversionRate("AED", "IRR", 119473.0);// UAE Dirham to Iranian Rial
    setConversionRate("AED", "JPY", 311.33);  // UAE Dirham to Japanese Yen
    setConversionRate("AED", "KRW", 3215.49); // UAE Dirham to South Korean Won
    setConversionRate("AED", "MXN", 57.05);   // UAE Dirham to Mexican Peso
    setConversionRate("AED", "NOK", 2.50);    // UAE Dirham to Norwegian Krone
    setConversionRate("AED", "NZD", 0.41);    // UAE Dirham to New Zealand Dollar
    setConversionRate("AED", "PLN", 1.10);    // UAE Dirham to Polish Zloty
    setConversionRate("AED", "RUB", 20.98);   // UAE Dirham to Russian Ruble
    setConversionRate("AED", "SAR", 1.08);    // UAE Dirham to Saudi Riyal
    setConversionRate("AED", "SEK", 2.54);    // UAE Dirham to Swedish Krona
    setConversionRate("AED", "TRY", 2.44);    // UAE Dirham to Turkish Lira
    setConversionRate("AED", "ZAR", 4.30);    // UAE Dirham to South African Rand
}

void CurrencyConverter::setAUDConversionRates(){
    setConversionRate("AUD", "USD", 0.74);    // Australian Dollar to USD
    setConversionRate("AUD", "AED", 2.80);    // Australian Dollar to UAE Dirham
    setConversionRate("AUD", "BRL", 3.80);    // Australian Dollar to Brazilian Real
    setConversionRate("AUD", "CAD", 0.91);    // Australian Dollar to Canadian Dollar
    setConversionRate("AUD", "CHF", 0.67);    // Australian Dollar to Swiss Franc
    setConversionRate("AUD", "CNY", 4.76);    // Australian Dollar to Chinese Yuan
    setConversionRate("AUD", "EGP", 18.41);   // Australian Dollar to Egyptian Pound
    setConversionRate("AUD", "EUR", 0.62);    // Australian Dollar to Euro
    setConversionRate("AUD", "GBP", 0.54);    // Australian Dollar to British Pound
    setConversionRate("AUD", "HKD", 5.12);    // Australian Dollar to Hong Kong Dollar
    setConversionRate("AUD", "INR", 53.14);   // Australian Dollar to Indian Rupee
    setConversionRate("AUD", "IRR", 29743.47); // Australian Dollar to Iranian Rial
    setConversionRate("AUD", "JPY", 81.50);   // Australian Dollar to Japanese Yen
    setConversionRate("AUD", "KRW", 852.78);  // Australian Dollar to South Korean Won
    setConversionRate("AUD", "MXN", 15.19);   // Australian Dollar to Mexican Peso
    setConversionRate("AUD", "NOK", 6.61);    // Australian Dollar to Norwegian Krone
    setConversionRate("AUD", "NZD", 1.07);    // Australian Dollar to New Zealand Dollar
    setConversionRate("AUD", "PLN", 2.86);    // Australian Dollar to Polish Zloty
    setConversionRate("AUD", "RUB", 54.72);   // Australian Dollar to Russian Ruble
    setConversionRate("AUD", "SAR", 2.78);    // Australian Dollar to Saudi Riyal
    setConversionRate("AUD", "SEK", 6.64);    // Australian Dollar to Swedish Krona
    setConversionRate("AUD", "TRY", 6.47);    // Australian Dollar to Turkish Lira
    setConversionRate("AUD", "ZAR", 10.76);   // Australian Dollar to South African Rand
}

void CurrencyConverter::setBRLConversionRates(){
    setConversionRate("BRL", "USD", 0.19);    // Brazilian Real to USD
    setConversionRate("BRL", "AED", 0.28);    // Brazilian Real to UAE Dirham
    setConversionRate("BRL", "AUD", 0.26);    // Brazilian Real to Australian Dollar
    setConversionRate("BRL", "CAD", 0.23);    // Brazilian Real to Canadian Dollar
    setConversionRate("BRL", "CHF", 0.17);    // Brazilian Real to Swiss Franc
    setConversionRate("BRL", "CNY", 1.20);    // Brazilian Real to Chinese Yuan
    setConversionRate("BRL", "EGP", 4.66);    // Brazilian Real to Egyptian Pound
    setConversionRate("BRL", "EUR", 0.16);    // Brazilian Real to Euro
    setConversionRate("BRL", "GBP", 0.14);    // Brazilian Real to British Pound
    setConversionRate("BRL", "HKD", 1.36);    // Brazilian Real to Hong Kong Dollar
    setConversionRate("BRL", "INR", 14.08);   // Brazilian Real to Indian Rupee
    setConversionRate("BRL", "IRR", 7902.30); // Brazilian Real to Iranian Rial
    setConversionRate("BRL", "JPY", 21.68);   // Brazilian Real to Japanese Yen
    setConversionRate("BRL", "KRW", 226.92);  // Brazilian Real to South Korean Won
    setConversionRate("BRL", "MXN", 4.05);    // Brazilian Real to Mexican Peso
    setConversionRate("BRL", "NOK", 1.76);    // Brazilian Real to Norwegian Krone
    setConversionRate("BRL", "NZD", 0.28);    // Brazilian Real to New Zealand Dollar
    setConversionRate("BRL", "PLN", 0.75);    // Brazilian Real to Polish Zloty
    setConversionRate("BRL", "RUB", 14.38);   // Brazilian Real to Russian Ruble
    setConversionRate("BRL", "SAR", 0.28);    // Brazilian Real to Saudi Riyal
    setConversionRate("BRL", "SEK", 1.77);    // Brazilian Real to Swedish Krona
    setConversionRate("BRL", "TRY", 1.73);    // Brazilian Real to Turkish Lira
    setConversionRate("BRL", "ZAR", 2.87);    // Brazilian Real to South African Rand
}

void CurrencyConverter::setCADConversionRates(){
    setConversionRate("CAD", "USD", 0.81);    // Canadian Dollar to USD
    setConversionRate("CAD", "AED", 3.17);    // Canadian Dollar to UAE Dirham
    setConversionRate("CAD", "AUD", 1.17);    // Canadian Dollar to Australian Dollar
    setConversionRate("CAD", "BRL", 4.47);    // Canadian Dollar to Brazilian Real
    setConversionRate("CAD", "CHF", 0.74);    // Canadian Dollar to Swiss Franc
    setConversionRate("CAD", "CNY", 5.25);    // Canadian Dollar to Chinese Yuan
    setConversionRate("CAD", "EGP", 12.79);   // Canadian Dollar to Egyptian Pound
    setConversionRate("CAD", "EUR", 0.67);    // Canadian Dollar to Euro
    setConversionRate("CAD", "GBP", 0.59);    // Canadian Dollar to British Pound
    setConversionRate("CAD", "HKD", 6.41);    // Canadian Dollar to Hong Kong Dollar
    setConversionRate("CAD", "INR", 62.87);   // Canadian Dollar to Indian Rupee
    setConversionRate("CAD", "IRR", 35217.54); // Canadian Dollar to Iranian Rial
    setConversionRate("CAD", "JPY", 96.97);   // Canadian Dollar to Japanese Yen
    setConversionRate("CAD", "KRW", 1011.75); // Canadian Dollar to South Korean Won
    setConversionRate("CAD", "MXN", 18.06);   // Canadian Dollar to Mexican Peso
    setConversionRate("CAD", "NOK", 7.89);    // Canadian Dollar to Norwegian Krone
    setConversionRate("CAD", "NZD", 1.28);    // Canadian Dollar to New Zealand Dollar
    setConversionRate("CAD", "PLN", 3.43);    // Canadian Dollar to Polish Zloty
    setConversionRate("CAD", "RUB", 65.51);   // Canadian Dollar to Russian Ruble
    setConversionRate("CAD", "SAR", 3.15);    // Canadian Dollar to Saudi Riyal
    setConversionRate("CAD", "SEK", 7.48);    // Canadian Dollar to Swedish Krona
    setConversionRate("CAD", "TRY", 7.25);    // Canadian Dollar to Turkish Lira
    setConversionRate("CAD", "ZAR", 12.04);   // Canadian Dollar to South African Rand
}

void CurrencyConverter::setCHFConversionRates(){
    setConversionRate("CHF", "USD", 1.10);    // Swiss Franc to USD
    setConversionRate("CHF", "AED", 4.04);    // Swiss Franc to UAE Dirham
    setConversionRate("CHF", "AUD", 1.49);    // Swiss Franc to Australian Dollar
    setConversionRate("CHF", "BRL", 5.03);    // Swiss Franc to Brazilian Real
    setConversionRate("CHF", "CAD", 1.35);    // Swiss Franc to Canadian Dollar
    setConversionRate("CHF", "CNY", 7.01);    // Swiss Franc to Chinese Yuan
    setConversionRate("CHF", "EGP", 17.04);   // Swiss Franc to Egyptian Pound
    setConversionRate("CHF", "EUR", 0.89);    // Swiss Franc to Euro
    setConversionRate("CHF", "GBP", 0.78);    // Swiss Franc to British Pound
    setConversionRate("CHF", "HKD", 8.48);    // Swiss Franc to Hong Kong Dollar
    setConversionRate("CHF", "INR", 83.38);   // Swiss Franc to Indian Rupee
    setConversionRate("CHF", "IRR", 46760.88); // Swiss Franc to Iranian Rial
    setConversionRate("CHF", "JPY", 128.92);  // Swiss Franc to Japanese Yen
    setConversionRate("CHF", "KRW", 1349.79); // Swiss Franc to South Korean Won
    setConversionRate("CHF", "MXN", 24.01);   // Swiss Franc to Mexican Peso
    setConversionRate("CHF", "NOK", 10.49);   // Swiss Franc to Norwegian Krone
    setConversionRate("CHF", "NZD", 1.69);    // Swiss Franc to New Zealand Dollar
    setConversionRate("CHF", "PLN", 4.53);    // Swiss Franc to Polish Zloty
    setConversionRate("CHF", "RUB", 86.35);   // Swiss Franc to Russian Ruble
    setConversionRate("CHF", "SAR", 4.00);    // Swiss Franc to Saudi Riyal
    setConversionRate("CHF", "SEK", 9.48);    // Swiss Franc to Swedish Krona
    setConversionRate("CHF", "TRY", 9.19);    // Swiss Franc to Turkish Lira
    setConversionRate("CHF", "ZAR", 15.20);   // Swiss Franc to South African Rand
}

void CurrencyConverter::setCNYConversionRates(){
    setConversionRate("CNY", "USD", 0.15);    // Chinese Yuan to USD
    setConversionRate("CNY", "AED", 0.55);    // Chinese Yuan to UAE Dirham
    setConversionRate("CNY", "AUD", 0.20);    // Chinese Yuan to Australian Dollar
    setConversionRate("CNY", "BRL", 0.70);    // Chinese Yuan to Brazilian Real
    setConversionRate("CNY", "CAD", 0.19);    // Chinese Yuan to Canadian Dollar
    setConversionRate("CNY", "CHF", 0.14);    // Chinese Yuan to Swiss Franc
    setConversionRate("CNY", "EGP", 2.44);    // Chinese Yuan to Egyptian Pound
    setConversionRate("CNY", "EUR", 0.13);    // Chinese Yuan to Euro
    setConversionRate("CNY", "GBP", 0.11);    // Chinese Yuan to British Pound
    setConversionRate("CNY", "HKD", 1.18);    // Chinese Yuan to Hong Kong Dollar
    setConversionRate("CNY", "INR", 11.56);   // Chinese Yuan to Indian Rupee
    setConversionRate("CNY", "IRR", 64894.80); // Chinese Yuan to Iranian Rial
    setConversionRate("CNY", "JPY", 178.43);  // Chinese Yuan to Japanese Yen
    setConversionRate("CNY", "KRW", 1870.46); // Chinese Yuan to South Korean Won
    setConversionRate("CNY", "MXN", 33.28);   // Chinese Yuan to Mexican Peso
    setConversionRate("CNY", "NOK", 14.55);   // Chinese Yuan to Norwegian Krone
    setConversionRate("CNY", "NZD", 0.24);    // Chinese Yuan to New Zealand Dollar
    setConversionRate("CNY", "PLN", 0.64);    // Chinese Yuan to Polish Zloty
    setConversionRate("CNY", "RUB", 12.21);   // Chinese Yuan to Russian Ruble
    setConversionRate("CNY", "SAR", 0.57);    // Chinese Yuan to Saudi Riyal
    setConversionRate("CNY", "SEK", 1.36);    // Chinese Yuan to Swedish Krona
    setConversionRate("CNY", "TRY", 1.32);    // Chinese Yuan to Turkish Lira
    setConversionRate("CNY", "ZAR", 2.18);    // Chinese Yuan to South African Rand
}

void CurrencyConverter::setEGPConversionRates(){
    setConversionRate("EGP", "USD", 0.063);    // Egyptian Pound to USD
    setConversionRate("EGP", "AED", 0.23);     // Egyptian Pound to UAE Dirham
    setConversionRate("EGP", "AUD", 0.086);    // Egyptian Pound to Australian Dollar
    setConversionRate("EGP", "BRL", 0.30);     // Egyptian Pound to Brazilian Real
    setConversionRate("EGP", "CAD", 0.082);    // Egyptian Pound to Canadian Dollar
    setConversionRate("EGP", "CHF", 0.058);    // Egyptian Pound to Swiss Franc
    setConversionRate("EGP", "CNY", 0.41);     // Egyptian Pound to Chinese Yuan
    setConversionRate("EGP", "EUR", 0.052);    // Egyptian Pound to Euro
    setConversionRate("EGP", "GBP", 0.045);    // Egyptian Pound to British Pound
    setConversionRate("EGP", "HKD", 0.49);     // Egyptian Pound to Hong Kong Dollar
    setConversionRate("EGP", "INR", 4.79);     // Egyptian Pound to Indian Rupee
    setConversionRate("EGP", "IRR", 2689.97);  // Egyptian Pound to Iranian Rial
    setConversionRate("EGP", "JPY", 7.41);     // Egyptian Pound to Japanese Yen
    setConversionRate("EGP", "KRW", 77.71);    // Egyptian Pound to South Korean Won
    setConversionRate("EGP", "MXN", 1.38);     // Egyptian Pound to Mexican Peso
    setConversionRate("EGP", "NOK", 0.60);     // Egyptian Pound to Norwegian Krone
    setConversionRate("EGP", "NZD", 0.098);    // Egyptian Pound to New Zealand Dollar
    setConversionRate("EGP", "PLN", 0.26);     // Egyptian Pound to Polish Zloty
    setConversionRate("EGP", "RUB", 4.99);     // Egyptian Pound to Russian Ruble
    setConversionRate("EGP", "SAR", 0.23);     // Egyptian Pound to Saudi Riyal
    setConversionRate("EGP", "SEK", 0.55);     // Egyptian Pound to Swedish Krona
    setConversionRate("EGP", "TRY", 0.53);     // Egyptian Pound to Turkish Lira
    setConversionRate("EGP", "ZAR", 0.87);     // Egyptian Pound to South African Rand
}

void CurrencyConverter::setEURConversionRates(){
    setConversionRate("EUR", "USD", 1.20);    // Euro to USD
    setConversionRate("EUR", "AED", 4.37);    // Euro to UAE Dirham
    setConversionRate("EUR", "AUD", 1.61);    // Euro to Australian Dollar
    setConversionRate("EUR", "BRL", 6.26);    // Euro to Brazilian Real
    setConversionRate("EUR", "CAD", 1.46);    // Euro to Canadian Dollar
    setConversionRate("EUR", "CHF", 1.08);    // Euro to Swiss Franc
    setConversionRate("EUR", "CNY", 7.73);    // Euro to Chinese Yuan
    setConversionRate("EUR", "EGP", 19.19);   // Euro to Egyptian Pound
    setConversionRate("EUR", "GBP", 0.87);    // Euro to British Pound
    setConversionRate("EUR", "HKD", 9.49);    // Euro to Hong Kong Dollar
    setConversionRate("EUR", "INR", 88.67);   // Euro to Indian Rupee
    setConversionRate("EUR", "IRR", 49755.67); // Euro to Iranian Rial
    setConversionRate("EUR", "JPY", 129.47);  // Euro to Japanese Yen
    setConversionRate("EUR", "KRW", 1354.31); // Euro to South Korean Won
    setConversionRate("EUR", "MXN", 24.05);   // Euro to Mexican Peso
    setConversionRate("EUR", "NOK", 10.53);   // Euro to Norwegian Krone
    setConversionRate("EUR", "NZD", 1.73);    // Euro to New Zealand Dollar
    setConversionRate("EUR", "PLN", 4.61);    // Euro to Polish Zloty
    setConversionRate("EUR", "RUB", 88.05);   // Euro to Russian Ruble
    setConversionRate("EUR", "SAR", 4.52);    // Euro to Saudi Riyal
    setConversionRate("EUR", "SEK", 10.71);   // Euro to Swedish Krona
    setConversionRate("EUR", "TRY", 10.34);   // Euro to Turkish Lira
    setConversionRate("EUR", "ZAR", 17.13);   // Euro to South African Rand
}

void CurrencyConverter::setGBPConversionRates(){
    setConversionRate("GBP", "USD", 1.39);    // British Pound to USD
    setConversionRate("GBP", "AED", 5.07);    // British Pound to UAE Dirham
    setConversionRate("GBP", "AUD", 1.87);    // British Pound to Australian Dollar
    setConversionRate("GBP", "BRL", 7.28);    // British Pound to Brazilian Real
    setConversionRate("GBP", "CAD", 1.70);    // British Pound to Canadian Dollar
    setConversionRate("GBP", "CHF", 1.26);    // British Pound to Swiss Franc
    setConversionRate("GBP", "CNY", 9.04);    // British Pound to Chinese Yuan
    setConversionRate("GBP", "EGP", 22.02);   // British Pound to Egyptian Pound
    setConversionRate("GBP", "EUR", 1.14);    // British Pound to Euro
    setConversionRate("GBP", "HKD", 10.89);   // British Pound to Hong Kong Dollar
    setConversionRate("GBP", "INR", 102.01);  // British Pound to Indian Rupee
    setConversionRate("GBP", "IRR", 57348.38); // British Pound to Iranian Rial
    setConversionRate("GBP", "JPY", 149.44);  // British Pound to Japanese Yen
    setConversionRate("GBP", "KRW", 1566.41); // British Pound to South Korean Won
    setConversionRate("GBP", "MXN", 27.86);   // British Pound to Mexican Peso
    setConversionRate("GBP", "NOK", 12.17);   // British Pound to Norwegian Krone
    setConversionRate("GBP", "NZD", 2.00);    // British Pound to New Zealand Dollar
    setConversionRate("GBP", "PLN", 5.32);    // British Pound to Polish Zloty
    setConversionRate("GBP", "RUB", 101.33);  // British Pound to Russian Ruble
    setConversionRate("GBP", "SAR", 5.19);    // British Pound to Saudi Riyal
    setConversionRate("GBP", "SEK", 12.31);   // British Pound to Swedish Krona
    setConversionRate("GBP", "TRY", 11.90);   // British Pound to Turkish Lira
    setConversionRate("GBP", "ZAR", 19.70);   // British Pound to South African Rand
}

void CurrencyConverter::setHKDConversionRates(){
    setConversionRate("HKD", "USD", 0.13);    // Hong Kong Dollar to USD
    setConversionRate("HKD", "AED", 0.36);    // Hong Kong Dollar to UAE Dirham
    setConversionRate("HKD", "AUD", 0.53);    // Hong Kong Dollar to Australian Dollar
    setConversionRate("HKD", "BRL", 2.07);    // Hong Kong Dollar to Brazilian Real
    setConversionRate("HKD", "CAD", 0.48);    // Hong Kong Dollar to Canadian Dollar
    setConversionRate("HKD", "CHF", 0.36);    // Hong Kong Dollar to Swiss Franc
    setConversionRate("HKD", "CNY", 2.58);    // Hong Kong Dollar to Chinese Yuan
    setConversionRate("HKD", "EGP", 6.33);    // Hong Kong Dollar to Egyptian Pound
    setConversionRate("HKD", "EUR", 0.11);    // Hong Kong Dollar to Euro
    setConversionRate("HKD", "GBP", 0.09);    // Hong Kong Dollar to British Pound
    setConversionRate("HKD", "INR", 9.85);    // Hong Kong Dollar to Indian Rupee
    setConversionRate("HKD", "IRR", 5525.43); // Hong Kong Dollar to Iranian Rial
    setConversionRate("HKD", "JPY", 14.35);   // Hong Kong Dollar to Japanese Yen
    setConversionRate("HKD", "KRW", 150.26);  // Hong Kong Dollar to South Korean Won
    setConversionRate("HKD", "MXN", 2.67);    // Hong Kong Dollar to Mexican Peso
    setConversionRate("HKD", "NOK", 1.17);    // Hong Kong Dollar to Norwegian Krone
    setConversionRate("HKD", "NZD", 0.63);    // Hong Kong Dollar to New Zealand Dollar
    setConversionRate("HKD", "PLN", 1.67);    // Hong Kong Dollar to Polish Zloty
    setConversionRate("HKD", "RUB", 31.74);   // Hong Kong Dollar to Russian Ruble
    setConversionRate("HKD", "SAR", 1.62);    // Hong Kong Dollar to Saudi Riyal
    setConversionRate("HKD", "SEK", 1.89);    // Hong Kong Dollar to Swedish Krona
    setConversionRate("HKD", "TRY", 1.82);    // Hong Kong Dollar to Turkish Lira
    setConversionRate("HKD", "ZAR", 3.02);    // Hong Kong Dollar to South African Rand
}

void CurrencyConverter::setINRConversionRates(){
    setConversionRate("INR", "USD", 0.013);    // Indian Rupee to USD
    setConversionRate("INR", "AED", 0.047);    // Indian Rupee to UAE Dirham
    setConversionRate("INR", "AUD", 0.018);    // Indian Rupee to Australian Dollar
    setConversionRate("INR", "BRL", 0.072);    // Indian Rupee to Brazilian Real
    setConversionRate("INR", "CAD", 0.017);    // Indian Rupee to Canadian Dollar
    setConversionRate("INR", "CHF", 0.013);    // Indian Rupee to Swiss Franc
    setConversionRate("INR", "CNY", 0.092);    // Indian Rupee to Chinese Yuan
    setConversionRate("INR", "EGP", 0.23);     // Indian Rupee to Egyptian Pound
    setConversionRate("INR", "EUR", 0.011);    // Indian Rupee to Euro
    setConversionRate("INR", "GBP", 0.009);    // Indian Rupee to British Pound
    setConversionRate("INR", "HKD", 0.10);     // Indian Rupee to Hong Kong Dollar
    setConversionRate("INR", "IRR", 563.63);   // Indian Rupee to Iranian Rial
    setConversionRate("INR", "JPY", 1.47);     // Indian Rupee to Japanese Yen
    setConversionRate("INR", "KRW", 15.43);    // Indian Rupee to South Korean Won
    setConversionRate("INR", "MXN", 0.27);     // Indian Rupee to Mexican Peso
    setConversionRate("INR", "NOK", 0.12);     // Indian Rupee to Norwegian Krone
    setConversionRate("INR", "NZD", 0.020);    // Indian Rupee to New Zealand Dollar
    setConversionRate("INR", "PLN", 0.053);    // Indian Rupee to Polish Zloty
    setConversionRate("INR", "RUB", 1.01);     // Indian Rupee to Russian Ruble
    setConversionRate("INR", "SAR", 0.052);    // Indian Rupee to Saudi Riyal
    setConversionRate("INR", "SEK", 0.12);     // Indian Rupee to Swedish Krona
    setConversionRate("INR", "TRY", 0.11);     // Indian Rupee to Turkish Lira
    setConversionRate("INR", "ZAR", 0.18);     // Indian Rupee to South African Rand
}

void CurrencyConverter::setIRRConversionRates(){
    setConversionRate("IRR", "USD", 0.000024);  // Iranian Rial to USD
    setConversionRate("IRR", "AED", 0.000089);  // Iranian Rial to UAE Dirham
    setConversionRate("IRR", "AUD", 0.000034);  // Iranian Rial to Australian Dollar
    setConversionRate("IRR", "BRL", 0.000133);  // Iranian Rial to Brazilian Real
    setConversionRate("IRR", "CAD", 0.000031);  // Iranian Rial to Canadian Dollar
    setConversionRate("IRR", "CHF", 0.000024);  // Iranian Rial to Swiss Franc
    setConversionRate("IRR", "CNY", 0.000171);  // Iranian Rial to Chinese Yuan
    setConversionRate("IRR", "EGP", 0.000420);  // Iranian Rial to Egyptian Pound
    setConversionRate("IRR", "EUR", 0.000021);  // Iranian Rial to Euro
    setConversionRate("IRR", "GBP", 0.000017);  // Iranian Rial to British Pound
    setConversionRate("IRR", "HKD", 0.000181);  // Iranian Rial to Hong Kong Dollar
    setConversionRate("IRR", "INR", 0.001780);  // Iranian Rial to Indian Rupee
    setConversionRate("IRR", "JPY", 0.00283);   // Iranian Rial to Japanese Yen
    setConversionRate("IRR", "KRW", 0.02978);   // Iranian Rial to South Korean Won
    setConversionRate("IRR", "MXN", 0.000053);  // Iranian Rial to Mexican Peso
    setConversionRate("IRR", "NOK", 0.000236);  // Iranian Rial to Norwegian Krone
    setConversionRate("IRR", "NZD", 0.000039);  // Iranian Rial to New Zealand Dollar
    setConversionRate("IRR", "PLN", 0.000104);  // Iranian Rial to Polish Zloty
    setConversionRate("IRR", "RUB", 0.001981);  // Iranian Rial to Russian Ruble
    setConversionRate("IRR", "SAR", 0.000102);  // Iranian Rial to Saudi Riyal
    setConversionRate("IRR", "SEK", 0.000237);  // Iranian Rial to Swedish Krona
    setConversionRate("IRR", "TRY", 0.000228);  // Iranian Rial to Turkish Lira
    setConversionRate("IRR", "ZAR", 0.000376);  // Iranian Rial to South African Rand
}

void CurrencyConverter::setJPYConversionRates(){
    setConversionRate("JPY", "USD", 0.0091);    // Japanese Yen to USD
    setConversionRate("JPY", "AED", 0.0336);    // Japanese Yen to UAE Dirham
    setConversionRate("JPY", "AUD", 0.0127);    // Japanese Yen to Australian Dollar
    setConversionRate("JPY", "BRL", 0.0499);    // Japanese Yen to Brazilian Real
    setConversionRate("JPY", "CAD", 0.0116);    // Japanese Yen to Canadian Dollar
    setConversionRate("JPY", "CHF", 0.0087);    // Japanese Yen to Swiss Franc
    setConversionRate("JPY", "CNY", 0.0617);    // Japanese Yen to Chinese Yuan
    setConversionRate("JPY", "EGP", 0.15);      // Japanese Yen to Egyptian Pound
    setConversionRate("JPY", "EUR", 0.0078);    // Japanese Yen to Euro
    setConversionRate("JPY", "GBP", 0.0066);    // Japanese Yen to British Pound
    setConversionRate("JPY", "HKD", 0.0715);    // Japanese Yen to Hong Kong Dollar
    setConversionRate("JPY", "INR", 0.6801);    // Japanese Yen to Indian Rupee
    setConversionRate("JPY", "IRR", 353.46);    // Japanese Yen to Iranian Rial
    setConversionRate("JPY", "KRW", 10.52);     // Japanese Yen to South Korean Won
    setConversionRate("JPY", "MXN", 0.1876);    // Japanese Yen to Mexican Peso
    setConversionRate("JPY", "NOK", 0.0828);    // Japanese Yen to Norwegian Krone
    setConversionRate("JPY", "NZD", 0.0135);    // Japanese Yen to New Zealand Dollar
    setConversionRate("JPY", "PLN", 0.0359);    // Japanese Yen to Polish Zloty
    setConversionRate("JPY", "RUB", 0.6839);    // Japanese Yen to Russian Ruble
    setConversionRate("JPY", "SAR", 0.0353);    // Japanese Yen to Saudi Riyal
    setConversionRate("JPY", "SEK", 0.0831);    // Japanese Yen to Swedish Krona
    setConversionRate("JPY", "TRY", 0.0801);    // Japanese Yen to Turkish Lira
    setConversionRate("JPY", "ZAR", 0.1323);    // Japanese Yen to South African Rand
}

void CurrencyConverter::setKRWConversionRates(){
    setConversionRate("KRW", "USD", 0.00088);   // South Korean Won to USD
    setConversionRate("KRW", "AED", 0.0032);    // South Korean Won to UAE Dirham
    setConversionRate("KRW", "AUD", 0.0012);    // South Korean Won to Australian Dollar
    setConversionRate("KRW", "BRL", 0.0046);    // South Korean Won to Brazilian Real
    setConversionRate("KRW", "CAD", 0.0011);    // South Korean Won to Canadian Dollar
    setConversionRate("KRW", "CHF", 0.00082);   // South Korean Won to Swiss Franc
    setConversionRate("KRW", "CNY", 0.0058);    // South Korean Won to Chinese Yuan
    setConversionRate("KRW", "EGP", 0.014);     // South Korean Won to Egyptian Pound
    setConversionRate("KRW", "EUR", 0.00074);   // South Korean Won to Euro
    setConversionRate("KRW", "GBP", 0.00063);   // South Korean Won to British Pound
    setConversionRate("KRW", "HKD", 0.0069);    // South Korean Won to Hong Kong Dollar
    setConversionRate("KRW", "INR", 0.066);     // South Korean Won to Indian Rupee
    setConversionRate("KRW", "IRR", 0.0336);    // South Korean Won to Iranian Rial
    setConversionRate("KRW", "JPY", 0.095);     // South Korean Won to Japanese Yen
    setConversionRate("KRW", "MXN", 0.0018);    // South Korean Won to Mexican Peso
    setConversionRate("KRW", "NOK", 0.0079);    // South Korean Won to Norwegian Krone
    setConversionRate("KRW", "NZD", 0.0013);    // South Korean Won to New Zealand Dollar
    setConversionRate("KRW", "PLN", 0.0035);    // South Korean Won to Polish Zloty
    setConversionRate("KRW", "RUB", 0.0669);    // South Korean Won to Russian Ruble
    setConversionRate("KRW", "SAR", 0.0034);    // South Korean Won to Saudi Riyal
    setConversionRate("KRW", "SEK", 0.008);     // South Korean Won to Swedish Krona
    setConversionRate("KRW", "TRY", 0.0077);    // South Korean Won to Turkish Lira
    setConversionRate("KRW", "ZAR", 0.0127);    // South Korean Won to South African Rand
}

void CurrencyConverter::setMXNConversionRates(){
    setConversionRate("MXN", "USD", 0.049);     // Mexican Peso to USD
    setConversionRate("MXN", "AED", 0.18);      // Mexican Peso to UAE Dirham
    setConversionRate("MXN", "AUD", 0.067);     // Mexican Peso to Australian Dollar
    setConversionRate("MXN", "BRL", 0.26);      // Mexican Peso to Brazilian Real
    setConversionRate("MXN", "CAD", 0.061);     // Mexican Peso to Canadian Dollar
    setConversionRate("MXN", "CHF", 0.045);     // Mexican Peso to Swiss Franc
    setConversionRate("MXN", "CNY", 0.32);      // Mexican Peso to Chinese Yuan
    setConversionRate("MXN", "EGP", 0.78);      // Mexican Peso to Egyptian Pound
    setConversionRate("MXN", "EUR", 0.041);     // Mexican Peso to Euro
    setConversionRate("MXN", "GBP", 0.035);     // Mexican Peso to British Pound
    setConversionRate("MXN", "HKD", 0.38);      // Mexican Peso to Hong Kong Dollar
    setConversionRate("MXN", "INR", 3.6);       // Mexican Peso to Indian Rupee
    setConversionRate("MXN", "IRR", 1826.1);    // Mexican Peso to Iranian Rial
    setConversionRate("MXN", "JPY", 5.46);      // Mexican Peso to Japanese Yen
    setConversionRate("MXN", "KRW", 546.14);    // Mexican Peso to South Korean Won
    setConversionRate("MXN", "NOK", 0.24);      // Mexican Peso to Norwegian Krone
    setConversionRate("MXN", "NZD", 0.038);     // Mexican Peso to New Zealand Dollar
    setConversionRate("MXN", "PLN", 0.1);       // Mexican Peso to Polish Zloty
    setConversionRate("MXN", "RUB", 1.92);      // Mexican Peso to Russian Ruble
    setConversionRate("MXN", "SAR", 0.097);     // Mexican Peso to Saudi Riyal
    setConversionRate("MXN", "SEK", 0.23);      // Mexican Peso to Swedish Krona
    setConversionRate("MXN", "TRY", 0.22);      // Mexican Peso to Turkish Lira
    setConversionRate("MXN", "ZAR", 0.36);      // Mexican Peso to South African Rand
}

void CurrencyConverter::setNOKConversionRates(){
    setConversionRate("NOK", "USD", 0.113);     // Norwegian Krone to USD
    setConversionRate("NOK", "AED", 0.41);      // Norwegian Krone to UAE Dirham
    setConversionRate("NOK", "AUD", 0.15);      // Norwegian Krone to Australian Dollar
    setConversionRate("NOK", "BRL", 0.59);      // Norwegian Krone to Brazilian Real
    setConversionRate("NOK", "CAD", 0.14);      // Norwegian Krone to Canadian Dollar
    setConversionRate("NOK", "CHF", 0.105);     // Norwegian Krone to Swiss Franc
    setConversionRate("NOK", "CNY", 0.74);      // Norwegian Krone to Chinese Yuan
    setConversionRate("NOK", "EGP", 1.79);      // Norwegian Krone to Egyptian Pound
    setConversionRate("NOK", "EUR", 0.094);     // Norwegian Krone to Euro
    setConversionRate("NOK", "GBP", 0.081);     // Norwegian Krone to British Pound
    setConversionRate("NOK", "HKD", 0.88);      // Norwegian Krone to Hong Kong Dollar
    setConversionRate("NOK", "INR", 8.3);       // Norwegian Krone to Indian Rupee
    setConversionRate("NOK", "IRR", 4209.5);    // Norwegian Krone to Iranian Rial
    setConversionRate("NOK", "JPY", 12.58);     // Norwegian Krone to Japanese Yen
    setConversionRate("NOK", "KRW", 1256.71);   // Norwegian Krone to South Korean Won
    setConversionRate("NOK", "MXN", 4.14);      // Norwegian Krone to Mexican Peso
    setConversionRate("NOK", "NZD", 0.17);      // Norwegian Krone to New Zealand Dollar
    setConversionRate("NOK", "PLN", 0.45);      // Norwegian Krone to Polish Zloty
    setConversionRate("NOK", "RUB", 8.6);       // Norwegian Krone to Russian Ruble
    setConversionRate("NOK", "SAR", 0.44);      // Norwegian Krone to Saudi Riyal
    setConversionRate("NOK", "SEK", 1.05);      // Norwegian Krone to Swedish Krona
    setConversionRate("NOK", "TRY", 0.97);      // Norwegian Krone to Turkish Lira
    setConversionRate("NOK", "ZAR", 1.61);      // Norwegian Krone to South African Rand
}

void CurrencyConverter::setNZDConversionRates(){
    setConversionRate("NZD", "USD", 0.7);       // New Zealand Dollar to USD
    setConversionRate("NZD", "AED", 2.56);      // New Zealand Dollar to UAE Dirham
    setConversionRate("NZD", "AUD", 0.94);      // New Zealand Dollar to Australian Dollar
    setConversionRate("NZD", "BRL", 3.66);      // New Zealand Dollar to Brazilian Real
    setConversionRate("NZD", "CAD", 0.86);      // New Zealand Dollar to Canadian Dollar
    setConversionRate("NZD", "CHF", 0.64);      // New Zealand Dollar to Swiss Franc
    setConversionRate("NZD", "CNY", 4.5);       // New Zealand Dollar to Chinese Yuan
    setConversionRate("NZD", "EGP", 10.92);     // New Zealand Dollar to Egyptian Pound
    setConversionRate("NZD", "EUR", 0.57);      // New Zealand Dollar to Euro
    setConversionRate("NZD", "GBP", 0.49);      // New Zealand Dollar to British Pound
    setConversionRate("NZD", "HKD", 5.34);      // New Zealand Dollar to Hong Kong Dollar
    setConversionRate("NZD", "INR", 50.6);      // New Zealand Dollar to Indian Rupee
    setConversionRate("NZD", "IRR", 25447.9);   // New Zealand Dollar to Iranian Rial
    setConversionRate("NZD", "JPY", 76.04);     // New Zealand Dollar to Japanese Yen
    setConversionRate("NZD", "KRW", 758.12);    // New Zealand Dollar to South Korean Won
    setConversionRate("NZD", "MXN", 2.5);       // New Zealand Dollar to Mexican Peso
    setConversionRate("NZD", "NOK", 5.98);      // New Zealand Dollar to Norwegian Krone
    setConversionRate("NZD", "PLN", 2.66);      // New Zealand Dollar to Polish Zloty
    setConversionRate("NZD", "RUB", 50.54);     // New Zealand Dollar to Russian Ruble
    setConversionRate("NZD", "SAR", 2.56);      // New Zealand Dollar to Saudi Riyal
    setConversionRate("NZD", "SEK", 6.07);      // New Zealand Dollar to Swedish Krona
    setConversionRate("NZD", "TRY", 5.63);      // New Zealand Dollar to Turkish Lira
    setConversionRate("NZD", "ZAR", 9.3);       // New Zealand Dollar to South African Rand
}

void CurrencyConverter::setPLNConversionRates(){
    setConversionRate("PLN", "USD", 0.26);    // Polish Zloty to USD
    setConversionRate("PLN", "AED", 0.24);    // Polish Zloty to UAE Dirham
    setConversionRate("PLN", "AUD", 0.35);    // Polish Zloty to Australian Dollar
    setConversionRate("PLN", "BRL", 1.36);    // Polish Zloty to Brazilian Real
    setConversionRate("PLN", "CAD", 0.32);    // Polish Zloty to Canadian Dollar
    setConversionRate("PLN", "CHF", 0.23);    // Polish Zloty to Swiss Franc
    setConversionRate("PLN", "CNY", 1.63);    // Polish Zloty to Chinese Yuan
    setConversionRate("PLN", "EGP", 3.95);    // Polish Zloty to Egyptian Pound
    setConversionRate("PLN", "EUR", 0.21);    // Polish Zloty to Euro
    setConversionRate("PLN", "GBP", 0.18);    // Polish Zloty to British Pound
    setConversionRate("PLN", "HKD", 1.94);    // Polish Zloty to Hong Kong Dollar
    setConversionRate("PLN", "INR", 18.89);   // Polish Zloty to Indian Rupee
    setConversionRate("PLN", "IRR", 106093.0);// Polish Zloty to Iranian Rial
    setConversionRate("PLN", "JPY", 276.68);  // Polish Zloty to Japanese Yen
    setConversionRate("PLN", "KRW", 2863.75); // Polish Zloty to South Korean Won
    setConversionRate("PLN", "MXN", 50.90);   // Polish Zloty to Mexican Peso
    setConversionRate("PLN", "NOK", 2.23);    // Polish Zloty to Norwegian Krone
    setConversionRate("PLN", "NZD", 0.36);    // Polish Zloty to New Zealand Dollar
    setConversionRate("PLN", "RUB", 18.19);   // Polish Zloty to Russian Ruble
    setConversionRate("PLN", "SAR", 0.93);    // Polish Zloty to Saudi Riyal
    setConversionRate("PLN", "SEK", 2.18);    // Polish Zloty to Swedish Krona
    setConversionRate("PLN", "TRY", 2.10);    // Polish Zloty to Turkish Lira
    setConversionRate("PLN", "ZAR", 3.71);    // Polish Zloty to South African Rand
}

void CurrencyConverter::setRUBConversionRates(){
    setConversionRate("RUB", "USD", 0.014);     // Russian Ruble to USD
    setConversionRate("RUB", "AED", 0.051);     // Russian Ruble to UAE Dirham
    setConversionRate("RUB", "AUD", 0.019);     // Russian Ruble to Australian Dollar
    setConversionRate("RUB", "BRL", 0.073);     // Russian Ruble to Brazilian Real
    setConversionRate("RUB", "CAD", 0.017);     // Russian Ruble to Canadian Dollar
    setConversionRate("RUB", "CHF", 0.012);     // Russian Ruble to Swiss Franc
    setConversionRate("RUB", "CNY", 0.087);     // Russian Ruble to Chinese Yuan
    setConversionRate("RUB", "EGP", 0.212);     // Russian Ruble to Egyptian Pound
    setConversionRate("RUB", "EUR", 0.011);     // Russian Ruble to Euro
    setConversionRate("RUB", "GBP", 0.009);     // Russian Ruble to British Pound
    setConversionRate("RUB", "HKD", 0.098);     // Russian Ruble to Hong Kong Dollar
    setConversionRate("RUB", "INR", 0.925);     // Russian Ruble to Indian Rupee
    setConversionRate("RUB", "IRR", 464.61);    // Russian Ruble to Iranian Rial
    setConversionRate("RUB", "JPY", 1.39);      // Russian Ruble to Japanese Yen
    setConversionRate("RUB", "KRW", 13.89);     // Russian Ruble to South Korean Won
    setConversionRate("RUB", "MXN", 0.046);     // Russian Ruble to Mexican Peso
    setConversionRate("RUB", "NOK", 0.11);      // Russian Ruble to Norwegian Krone
    setConversionRate("RUB", "NZD", 0.019);     // Russian Ruble to New Zealand Dollar
    setConversionRate("RUB", "PLN", 0.052);     // Russian Ruble to Polish Zloty
    setConversionRate("RUB", "SAR", 0.053);     // Russian Ruble to Saudi Riyal
    setConversionRate("RUB", "SEK", 0.125);     // Russian Ruble to Swedish Krona
    setConversionRate("RUB", "TRY", 0.116);     // Russian Ruble to Turkish Lira
    setConversionRate("RUB", "ZAR", 0.192);     // Russian Ruble to South African Rand
}

void CurrencyConverter::setSARConversionRates(){
    setConversionRate("SAR", "USD", 0.27);      // Saudi Riyal to USD
    setConversionRate("SAR", "AED", 0.98);      // Saudi Riyal to UAE Dirham
    setConversionRate("SAR", "AUD", 0.36);      // Saudi Riyal to Australian Dollar
    setConversionRate("SAR", "BRL", 1.41);      // Saudi Riyal to Brazilian Real
    setConversionRate("SAR", "CAD", 0.33);      // Saudi Riyal to Canadian Dollar
    setConversionRate("SAR", "CHF", 0.25);      // Saudi Riyal to Swiss Franc
    setConversionRate("SAR", "CNY", 1.77);      // Saudi Riyal to Chinese Yuan
    setConversionRate("SAR", "EGP", 4.32);      // Saudi Riyal to Egyptian Pound
    setConversionRate("SAR", "EUR", 0.23);      // Saudi Riyal to Euro
    setConversionRate("SAR", "GBP", 0.2);       // Saudi Riyal to British Pound
    setConversionRate("SAR", "HKD", 2.18);      // Saudi Riyal to Hong Kong Dollar
    setConversionRate("SAR", "INR", 20.58);     // Saudi Riyal to Indian Rupee
    setConversionRate("SAR", "IRR", 10337.0);   // Saudi Riyal to Iranian Rial
    setConversionRate("SAR", "JPY", 30.99);     // Saudi Riyal to Japanese Yen
    setConversionRate("SAR", "KRW", 309.9);     // Saudi Riyal to South Korean Won
    setConversionRate("SAR", "MXN", 1.02);      // Saudi Riyal to Mexican Peso
    setConversionRate("SAR", "NOK", 2.42);      // Saudi Riyal to Norwegian Krone
    setConversionRate("SAR", "NZD", 0.41);      // Saudi Riyal to New Zealand Dollar
    setConversionRate("SAR", "PLN", 1.1);       // Saudi Riyal to Polish Zloty
    setConversionRate("SAR", "RUB", 18.87);     // Saudi Riyal to Russian Ruble
    setConversionRate("SAR", "SEK", 2.52);      // Saudi Riyal to Swedish Krona
    setConversionRate("SAR", "TRY", 2.35);      // Saudi Riyal to Turkish Lira
    setConversionRate("SAR", "ZAR", 3.89);      // Saudi Riyal to South African Rand
}

void CurrencyConverter::setSEKConversionRates() {
    setConversionRate("SEK", "USD", 0.11);    // Swedish Krona to USD
    setConversionRate("SEK", "AED", 0.41);    // Swedish Krona to UAE Dirham
    setConversionRate("SEK", "AUD", 0.15);    // Swedish Krona to Australian Dollar
    setConversionRate("SEK", "BRL", 0.59);    // Swedish Krona to Brazilian Real
    setConversionRate("SEK", "CAD", 0.14);    // Swedish Krona to Canadian Dollar
    setConversionRate("SEK", "CHF", 0.10);    // Swedish Krona to Swiss Franc
    setConversionRate("SEK", "CNY", 0.69);    // Swedish Krona to Chinese Yuan
    setConversionRate("SEK", "EGP", 1.68);    // Swedish Krona to Egyptian Pound
    setConversionRate("SEK", "EUR", 0.09);    // Swedish Krona to Euro
    setConversionRate("SEK", "GBP", 0.08);    // Swedish Krona to British Pound
    setConversionRate("SEK", "HKD", 0.87);    // Swedish Krona to Hong Kong Dollar
    setConversionRate("SEK", "INR", 8.49);    // Swedish Krona to Indian Rupee
    setConversionRate("SEK", "IRR", 47778.0); // Swedish Krona to Iranian Rial
    setConversionRate("SEK", "JPY", 124.40);  // Swedish Krona to Japanese Yen
    setConversionRate("SEK", "KRW", 1284.43); // Swedish Krona to South Korean Won
    setConversionRate("SEK", "MXN", 22.77);   // Swedish Krona to Mexican Peso
    setConversionRate("SEK", "NOK", 1.00);    // Swedish Krona to Norwegian Krone
    setConversionRate("SEK", "NZD", 0.16);    // Swedish Krona to New Zealand Dollar
    setConversionRate("SEK", "PLN", 0.45);    // Swedish Krona to Polish Zloty
    setConversionRate("SEK", "RUB", 11.41);   // Swedish Krona to Russian Ruble
    setConversionRate("SEK", "SAR", 0.58);    // Swedish Krona to Saudi Riyal
    setConversionRate("SEK", "TRY", 0.55);    // Swedish Krona to Turkish Lira
    setConversionRate("SEK", "ZAR", 1.94);    // Swedish Krona to South African Rand
}

void CurrencyConverter::setTRYConversionRates() {
    setConversionRate("TRY", "USD", 0.12);    // Turkish Lira to USD
    setConversionRate("TRY", "AED", 0.41);    // Turkish Lira to UAE Dirham
    setConversionRate("TRY", "AUD", 0.18);    // Turkish Lira to Australian Dollar
    setConversionRate("TRY", "BRL", 0.72);    // Turkish Lira to Brazilian Real
    setConversionRate("TRY", "CAD", 0.17);    // Turkish Lira to Canadian Dollar
    setConversionRate("TRY", "CHF", 0.13);    // Turkish Lira to Swiss Franc
    setConversionRate("TRY", "CNY", 0.90);    // Turkish Lira to Chinese Yuan
    setConversionRate("TRY", "EGP", 2.18);    // Turkish Lira to Egyptian Pound
    setConversionRate("TRY", "EUR", 0.11);    // Turkish Lira to Euro
    setConversionRate("TRY", "GBP", 0.10);    // Turkish Lira to British Pound
    setConversionRate("TRY", "HKD", 1.08);    // Turkish Lira to Hong Kong Dollar
    setConversionRate("TRY", "INR", 10.49);   // Turkish Lira to Indian Rupee
    setConversionRate("TRY", "IRR", 58754.0); // Turkish Lira to Iranian Rial
    setConversionRate("TRY", "JPY", 153.20);  // Turkish Lira to Japanese Yen
    setConversionRate("TRY", "KRW", 1586.77); // Turkish Lira to South Korean Won
    setConversionRate("TRY", "MXN", 28.14);   // Turkish Lira to Mexican Peso
    setConversionRate("TRY", "NOK", 1.23);    // Turkish Lira to Norwegian Krone
    setConversionRate("TRY", "NZD", 0.20);    // Turkish Lira to New Zealand Dollar
    setConversionRate("TRY", "PLN", 0.48);    // Turkish Lira to Polish Zloty
    setConversionRate("TRY", "RUB", 15.10);   // Turkish Lira to Russian Ruble
    setConversionRate("TRY", "SAR", 0.77);    // Turkish Lira to Saudi Riyal
    setConversionRate("TRY", "SEK", 1.82);    // Turkish Lira to Swedish Krona
    setConversionRate("TRY", "ZAR", 3.22);    // Turkish Lira to South African Rand
}


void CurrencyConverter::setUSDConversionRates(){
    setConversionRate("USD", "AED", 3.67);    // USD to UAE Dirham
    setConversionRate("USD", "AUD", 1.35);    // USD to Australian Dollar
    setConversionRate("USD", "BRL", 5.25);    // USD to Brazilian Real
    setConversionRate("USD", "CAD", 1.23);    // USD to Canadian Dollar
    setConversionRate("USD", "CHF", 0.91);    // USD to Swiss Franc
    setConversionRate("USD", "CNY", 6.48);    // USD to Chinese Yuan
    setConversionRate("USD", "EGP", 15.75);   // USD to Egyptian Pound
    setConversionRate("USD", "EUR", 0.83);    // USD to Euro
    setConversionRate("USD", "GBP", 0.72);    // USD to British Pound
    setConversionRate("USD", "HKD", 7.77);    // USD to Hong Kong Dollar
    setConversionRate("USD", "INR", 74.98);   // USD to Indian Rupee
    setConversionRate("USD", "IRR", 41666.66); // USD to Iranian Rial
    setConversionRate("USD", "JPY", 110.12);  // USD to Japanese Yen
    setConversionRate("USD", "KRW", 1135.0);  // USD to South Korean Won
    setConversionRate("USD", "MXN", 20.17);   // USD to Mexican Peso
    setConversionRate("USD", "NOK", 8.81);    // USD to Norwegian Krone
    setConversionRate("USD", "NZD", 1.43);    // USD to New Zealand Dollar
    setConversionRate("USD", "PLN", 3.83);    // USD to Polish Zloty
    setConversionRate("USD", "RUB", 73.13);   // USD to Russian Ruble
    setConversionRate("USD", "SAR", 3.75);    // USD to Saudi Riyal
    setConversionRate("USD", "SEK", 8.89);    // USD to Swedish Krona
    setConversionRate("USD", "TRY", 8.57);    // USD to Turkish Lira
    setConversionRate("USD", "ZAR", 14.25);   // USD to South African Rand
}

void CurrencyConverter::setZARConversionRates(){
    setConversionRate("ZAR", "USD", 0.07);    // South African Rand to USD
    setConversionRate("ZAR", "AED", 0.27);    // South African Rand to UAE Dirham
    setConversionRate("ZAR", "AUD", 0.1);     // South African Rand to Australian Dollar
    setConversionRate("ZAR", "BRL", 0.38);    // South African Rand to Brazilian Real
    setConversionRate("ZAR", "CAD", 0.09);    // South African Rand to Canadian Dollar
    setConversionRate("ZAR", "CHF", 0.07);    // South African Rand to Swiss Franc
    setConversionRate("ZAR", "CNY", 0.5);     // South African Rand to Chinese Yuan
    setConversionRate("ZAR", "EGP", 1.22);    // South African Rand to Egyptian Pound
    setConversionRate("ZAR", "EUR", 0.06);    // South African Rand to Euro
    setConversionRate("ZAR", "GBP", 0.05);    // South African Rand to British Pound
    setConversionRate("ZAR", "HKD", 0.54);    // South African Rand to Hong Kong Dollar
    setConversionRate("ZAR", "INR", 5.25);    // South African Rand to Indian Rupee
    setConversionRate("ZAR", "IRR", 2947.17); // South African Rand to Iranian Rial
    setConversionRate("ZAR", "JPY", 7.73);    // South African Rand to Japanese Yen
    setConversionRate("ZAR", "KRW", 79.63);   // South African Rand to South Korean Won
    setConversionRate("ZAR", "MXN", 1.41);    // South African Rand to Mexican Peso
    setConversionRate("ZAR", "NOK", 0.62);    // South African Rand to Norwegian Krone
    setConversionRate("ZAR", "NZD", 0.1);     // South African Rand to New Zealand Dollar
    setConversionRate("ZAR", "PLN", 0.27);    // South African Rand to Polish Zloty
    setConversionRate("ZAR", "RUB", 5.16);    // South African Rand to Russian Ruble
    setConversionRate("ZAR", "SAR", 0.27);    // South African Rand to Saudi Riyal
    setConversionRate("ZAR", "SEK", 0.62);    // South African Rand to Swedish Krona
    setConversionRate("ZAR", "TRY", 0.58);    // South African Rand to Turkish Lira
}

void CurrencyConverter::convertCurrency(Manufacturers *manufacturers, const std::string& fromCurrency, const std::string& toCurrency){
    for (Seller* seller : manufacturers->editManufacturers()){
        // convert products price
        for (Product& product : seller->editProducts().editProducts()){
            double currentValue = product.getPrice();
            double newValue = convert(fromCurrency, toCurrency, currentValue);
            product.setPrice(newValue);
        }

        // convert invoice items
        for (InvoiceItem& item : seller->editInvoiceItems().editItems()){
            double currentValue = item.getPrice();
            double newValue = convert(fromCurrency, toCurrency, currentValue);
            item.setPrice(newValue);
        }

        // convert available items for sales
        for (InvoiceItem& item : seller->editInvoice().editInvoiceItemModel().editItems()){
            double currentValue = item.getPrice();
            double newValue = convert(fromCurrency, toCurrency, currentValue);
            item.setPrice(newValue);
        }

        // convert purchase history invoice items
        for (Invoice& invoice : seller->editPurchaseModel().editInvoices()){
            for (InvoiceItem& item : invoice.editInvoiceItemModel().editItems()){
                double currentValue = item.getPrice();
                double newValue = convert(fromCurrency, toCurrency, currentValue);
                item.setPrice(newValue);
            }

            invoice.updateAmount();
        }

        // convert sold history invoice items
        for (Invoice& invoice : seller->editSoldModel().editInvoices()){
            for (InvoiceItem& item : invoice.editInvoiceItemModel().editItems()){
                double currentValue = item.getPrice();
                double newValue = convert(fromCurrency, toCurrency, currentValue);
                item.setPrice(newValue);
            }

            invoice.updateAmount();
        }
    }

    m_currencySymbol = m_currencySymbols[toCurrency];
    m_currency = toCurrency;
}

const std::string &CurrencyConverter::getCurrencySymbol() const{
    return m_currencySymbol;
}

const std::string &CurrencyConverter::getCurrentCurrency() const{
    return m_currency;
}

void CurrencyConverter::setCurrentCurrency(const std::string &currency){
    m_currency = currency;
    m_currencySymbol = m_currencySymbols[currency];
}

const std::string &CurrencyConverter::getSymbol() const{
    return m_currencySymbol;
}

const double CurrencyConverter::getRate(const std::string &baseCurrency, const std::string &quoteCurrency){
    std::string key = generateKey(baseCurrency, quoteCurrency);
    return m_conversionRates[key];

}

const std::map<std::string, double> &CurrencyConverter::getConversionRates() const{
    return m_conversionRates;
}

