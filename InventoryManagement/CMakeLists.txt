cmake_minimum_required(VERSION 3.5)

project(InventoryManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Copy the CSV file to the build directory
configure_file(data.csv ${CMAKE_CURRENT_BINARY_DIR}/data.csv COPYONLY)
configure_file(CurrencyExchangeRates.csv ${CMAKE_CURRENT_BINARY_DIR}/CurrencyExchangeRates.csv COPYONLY)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        product.h product.cpp
        user.h user.cpp
        seller.h seller.cpp
        products.h products.cpp
        purchase.h purchase.cpp
        sold.h sold.cpp
        invoiceItem.h invoiceItem.cpp
        invoiceItems.h invoiceItems.cpp
        Invoice.h Invoice.cpp
        resource.qrc
        customer_signup_page.h customer_signup_page.cpp customer_signup_page.ui
        seller_signup_window.h seller_signup_window.cpp seller_signup_window.ui
        home_window.h home_window.cpp home_window.ui
        inventory_widget.h inventory_widget.cpp inventory_widget.ui
        purchase_widget.h purchase_widget.cpp purchase_widget.ui
        reports_widget.h reports_widget.cpp reports_widget.ui
        currency_widget.h currency_widget.cpp currency_widget.ui
        invoice_widget.h invoice_widget.cpp invoice_widget.ui
        data.csv
        datahandler.h datahandler.cpp
        manufacturers.h manufacturers.cpp
        add_product_window.h add_product_window.cpp add_product_window.ui
        add_to_invoice.h add_to_invoice.cpp add_to_invoice.ui
        edit_product_window.h edit_product_window.cpp edit_product_window.ui
        product_information_window.h product_information_window.cpp product_information_window.ui
        CurrencyConverter.h CurrencyConverter.cpp
        Currency.h Currency.cpp
        CurrencyExchangeRates.csv
        edit_exchange_rate_window.h edit_exchange_rate_window.cpp edit_exchange_rate_window.ui
        purchase_invoice_window.h purchase_invoice_window.cpp purchase_invoice_window.ui
        sale_invoice_window.h sale_invoice_window.cpp sale_invoice_window.ui
        dataBase.db
        InvoiceNumbers.h InvoiceNumbers.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(InventoryManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET InventoryManagement APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(InventoryManagement SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(InventoryManagement
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(InventoryManagement PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(InventoryManagement PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS InventoryManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(InventoryManagement)
endif()
