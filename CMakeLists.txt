cmake_minimum_required(VERSION 3.10)
project(texstudio
        LANGUAGES C CXX
        VERSION 2.0.0
        DESCRIPTION "Texstudio"
        HOMEPAGE_URL "https://www.texstudio.org/"
        )


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

option(USE_QT4 "use Qt4 instead of Qt5" FALSE)
option(USE_PHONON "use Phonon" TRUE)
option(USE_SYSTEM_HUNSPELL "use system Hunspell" TRUE) #TODO
option(USE_SYSTEM_QUAZIP "use system Quazip" TRUE) #TODO
option(NO_CRASH_HANDLER "Don't use crash handler" FALSE)
option(NO_TESTS "Don't build tests" FALSE)
option(NO_POPPLER_PREVIEW "Don't use poppler preview" FALSE)
option(USE_ASAN "Build with AddressSanitizer" FALSE)
option(USE_IPO "Build with INTERPROCEDURAL OPTIMIZATION" FALSE)


if (UNIX AND NOT APPLE)
    set(LINUX 1)
endif()

if (NOT NO_TESTS AND CMAKE_BUILD_TYPE MATCHES "Debug")
    set(USE_TESTS 1)
endif()


if (NOT USE_QT4)
    set(USE_QT5 1)
endif()


add_library(texstudio_interface INTERFACE)

find_package(Threads REQUIRED)
target_link_libraries(texstudio_interface INTERFACE Threads::Threads)

find_package(ZLIB REQUIRED)
target_link_libraries(texstudio_interface INTERFACE ZLIB::ZLIB)

if (USE_QT5)
    find_package(Qt5 COMPONENTS Core Network Xml Svg Script PrintSupport Concurrent Widgets UiTools REQUIRED)
    target_link_libraries(texstudio_interface INTERFACE Qt5::Network Qt5::Xml Qt5::Svg Qt5::Script Qt5::PrintSupport
            Qt5::Concurrent Qt5::Widgets Qt5::UiTools)
    if (USE_PHONON)
        find_package(Phonon4Qt5 REQUIRED)
    endif()
else()
    find_package(Qt4 COMPONENTS Core Network Xml Svg Script PrintSupport Concurrent REQUIRED)
    if (USE_PHONON)
        find_package(Phonon REQUIRED)
    endif()
endif()

## TODO: src/qtsingleapplication/qtsinglecoreapplication.pri if not 4.3.x
if (TRUE)
    include_directories(src/qtsingleapplication)
    set(HEADERS ${HEADERS}
            src/qtsingleapplication/qtsinglecoreapplication.h
            src/qtsingleapplication/qtsingleapplication.h
            src/qtsingleapplication/qtlocalpeer.h)
    set(SOURCES ${SOURCES}
            src/qtsingleapplication/qtsinglecoreapplication.cpp
            src/qtsingleapplication/qtsingleapplication.cpp
            src/qtsingleapplication/qtlocalpeer.cpp)
else()
endif()

## sources.pri
include_directories(src)
set(HEADERS ${HEADERS}
        src/aboutdialog.h
        src/arraydialog.h
        src/bibtexdialog.h
        src/bibtexparser.h
        src/bibtexreader.h
        src/bidiextender.h
        src/bookmarks.h
        src/buildmanager.h
        src/cleandialog.h
        src/codesnippet.h
        src/configdialog.h
        src/configmanager.h
        src/configmanagerinterface.h
        src/cursorhistory.h
        src/cursorposition.h
        src/dblclickmenubar.h
        src/debughelper.h
        src/diff/diff_match_patch.h
        src/diffoperations.h
        src/directoryreader.h
        src/editors.h
        src/encoding.h
        src/encodingdialog.h
        src/filechooser.h
        src/fileselector.h
        src/flowlayout.h
        src/grammarcheck.h
        src/grammarcheck_config.h
        src/help.h
        src/icondelegate.h
        src/insertgraphics.h
        src/insertgraphics_config.h
        src/kpathseaParser.h
        src/latexcompleter.h
        src/latexcompleter_config.h
        src/latexcompleter_p.h
        src/latexdocument.h
        src/latexeditorview.h
        src/latexeditorview_config.h
        src/latexlog.h
        src/latexlogwidget.h
        src/latexoutputfilter.h
        src/latexpackage.h
        src/latexrepository.h
        src/latexstructure.h
        src/latexstyleparser.h
        src/letterdialog.h
        src/libqmarkedscrollbar/src/markedscrollbar.h
        src/logeditor.h
        src/loghighlighter.h
        src/maketemplatedialog.h
        src/manhattanstyle.h
        src/mathassistant.h
        src/minisplitter.h
        src/modifiedQObject.h
        src/mostQtHeaders.h
        src/pdfsplittool.h
        src/qmetautils.h
        src/quickbeamerdialog.h
        src/quickdocumentdialog.h
        src/randomtextgenerator.h
        src/scriptengine.h
        src/scriptobject.h
        src/searchquery.h
        src/searchresultmodel.h
        src/searchresultwidget.h
        src/session.h
        src/sessionlist.h
        src/smallUsefulFunctions.h
        src/spellerdialog.h
        src/spellerutility.h
        src/structuretreeview.h
        src/styleanimator.h
        src/stylehelper.h
        src/svn.h
        src/syntaxcheck.h
        src/tabbingdialog.h
        src/tabdialog.h
        src/tablemanipulation.h
        src/templatemanager.h
        src/templatemanager_p.h
        src/templateselector.h
        src/texdocdialog.h
        src/texstudio.h
        src/textanalysis.h
        src/thesaurusdialog.h
        src/titledpanel.h
        src/toolwidgets.h
        src/txstabwidget.h
        src/unicodeinsertion.h
        src/universalinputdialog.h
        src/unixutils.h
        src/updatechecker.h
        src/usermacro.h
        src/usermenudialog.h
        src/userquickdialog.h
        src/utilsSystem.h
        src/utilsUI.h
        src/utilsVersion.h
        src/webpublishdialog.h
        src/webpublishdialog_config.h
        src/xmltagslistwidget.h
        src/filedialog.h
        src/macrobrowserui.h)

set(SOURCES ${SOURCES}
        src/aboutdialog.cpp
        src/additionaltranslations.cpp
        src/arraydialog.cpp
        src/bibtexdialog.cpp
        src/bibtexparser.cpp
        src/bibtexreader.cpp
        src/bidiextender.cpp
        src/bookmarks.cpp
        src/buildmanager.cpp
        src/cleandialog.cpp
        src/codesnippet.cpp
        src/configdialog.cpp
        src/configmanager.cpp
        src/cursorhistory.cpp
        src/cursorposition.cpp
        src/dblclickmenubar.cpp
        src/debughelper.cpp
        src/diff/diff_match_patch.cpp
        src/diffoperations.cpp
        src/directoryreader.cpp
        src/editors.cpp
        src/encoding.cpp
        src/encodingdialog.cpp
        src/filechooser.cpp
        src/fileselector.cpp
        src/flowlayout.cpp
        src/grammarcheck.cpp
        src/help.cpp
        src/icondelegate.cpp
        src/insertgraphics.cpp
        src/kpathseaParser.cpp
        src/latexcompleter.cpp
        src/latexdocument.cpp
        src/latexeditorview.cpp
        src/latexlog.cpp
        src/latexlogwidget.cpp
        src/latexoutputfilter.cpp
        src/latexpackage.cpp
        src/latexrepository.cpp
        src/latexstructure.cpp
        src/latexstyleparser.cpp
        src/letterdialog.cpp
        src/libqmarkedscrollbar/src/markedscrollbar.cpp
        src/logeditor.cpp
        src/loghighlighter.cpp
        src/maketemplatedialog.cpp
        src/manhattanstyle.cpp
        src/mathassistant.cpp
        src/minisplitter.cpp
        src/pdfsplittool.cpp
        src/qmetautils.cpp
        src/quickbeamerdialog.cpp
        src/quickdocumentdialog.cpp
        src/randomtextgenerator.cpp
        src/scriptengine.cpp
        src/scriptobject.cpp
        src/searchquery.cpp
        src/searchresultmodel.cpp
        src/searchresultwidget.cpp
        src/session.cpp
        src/sessionlist.cpp
        src/smallUsefulFunctions.cpp
        src/spellerdialog.cpp
        src/spellerutility.cpp
        src/structuretreeview.cpp
        src/styleanimator.cpp
        src/stylehelper.cpp
        src/svn.cpp
        src/syntaxcheck.cpp
        src/tabbingdialog.cpp
        src/tabdialog.cpp
        src/tablemanipulation.cpp
        src/templatemanager.cpp
        src/templatemanager_p.cpp
        src/templateselector.cpp
        src/texdocdialog.cpp
        src/texstudio.cpp
        src/textanalysis.cpp
        src/thesaurusdialog.cpp
        src/titledpanel.cpp
        src/toolwidgets.cpp
        src/txstabwidget.cpp
        src/unicodeinsertion.cpp
        src/universalinputdialog.cpp
        src/unixutils.cpp
        src/updatechecker.cpp
        src/usermacro.cpp
        src/usermenudialog.cpp
        src/userquickdialog.cpp
        src/utilsSystem.cpp
        src/utilsUI.cpp
        src/utilsVersion.cpp
        src/webpublishdialog.cpp
        src/xmltagslistwidget.cpp
        src/filedialog.cpp
        src/macrobrowserui.cpp)
set(FORMS ${FORMS}
        src/aboutdialog.ui
        src/arraydialog.ui
        src/bibtexdialog.ui
        src/cleandialog.ui
        src/configdialog.ui
        src/encodingdialog.ui
        src/filechooser.ui
        src/insertgraphics.ui
        src/letterdialog.ui
        src/maketemplatedialog.ui
        src/pdfsplittool.ui
        src/quickbeamerdialog.ui
        src/quickdocumentdialog.ui
        src/randomtextgenerator.ui
        src/spellerdialog.ui
        src/tabbingdialog.ui
        src/tabdialog.ui
        src/templateselector.ui
        src/texdocdialog.ui
        src/textanalysis.ui
        src/usermenudialog.ui
        src/userquickdialog.ui
        src/webpublishdialog.ui)
if (WIN32)
    set(SOURCES ${SOURCES}
            src/utilssystem_win.cpp)
else()
    set(SOURCES ${SOURCES}
            src/utilssystem_unix.cpp)
endif()


set(TRANSLATIONS ${TRANSLATIONS}
        translation/texstudio_ar.ts
        translation/texstudio_br.ts
        translation/texstudio_cs.ts
        translation/texstudio_de.ts
        translation/texstudio_el.ts
        translation/texstudio_es.ts
        translation/texstudio_fa.ts
        translation/texstudio_fr.ts
        translation/texstudio_hu.ts
        translation/texstudio_id_ID.ts
        translation/texstudio_it.ts
        translation/texstudio_ja.ts
        translation/texstudio_ko.ts
        translation/texstudio_ko_KR.ts
        translation/texstudio_nl.ts
        translation/texstudio_pl.ts
        translation/texstudio_pt_BR.ts
        translation/texstudio_ru_RU.ts
        translation/texstudio_sv.ts
        translation/texstudio_tr_TR.ts
        translation/texstudio_uk.ts
        translation/texstudio_vi.ts
        translation/texstudio_zh_CN.ts)

set(RESOURCES ${RESOURCES}
        texstudio.qrc
        symbols.qrc
        completion.qrc
        images.qrc)

# xkb.pri
if (LINUX)
    include_directories(src/xkb)
    set(HEADERS ${HEADERS}
            src/xkb/XKeyboard.h
            src/xkb/X11Exception.h)
    set(SOURCES ${SOURCES}
            src/xkb/XKeyboard.cpp)
    find_package(X11 REQUIRED)
    target_link_libraries(texstudio_interface INTERFACE ${X11_LIBRARIES})
endif()

if (USE_SYSTEM_HUNSPELL)
    find_package(Hunspell REQUIRED)
    include_directories(${HUNSPELL_INCLUDE_DIRS})
    target_link_libraries(texstudio_interface INTERFACE ${HUNSPELL_LIBRARIES})
else()
    target_compile_definitions(texstudio_interface INTERFACE  HUNSPELL_STATIC)
    include_directories(src/hunspell)
    set(HEADERS ${HEADERS}
            src/hunspell/affentry.hxx
            src/hunspell/affixmgr.hxx
            src/hunspell/atypes.hxx
            src/hunspell/baseaffix.hxx
            src/hunspell/csutil.hxx
            src/hunspell/dictmgr.hxx
            src/hunspell/hashmgr.hxx
            src/hunspell/htypes.hxx
            src/hunspell/hunspell.hxx
            src/hunspell/hunspell.h
            src/hunspell/langnum.hxx
            src/hunspell/phonet.hxx
            src/hunspell/suggestmgr.hxx
            src/hunspell/filemgr.hxx
            src/hunspell/hunzip.hxx
            src/hunspell/w_char.hxx
            src/hunspell/replist.hxx)
    set(SOURCES ${SOURCES}
            src/hunspell/affentry.cxx
            src/hunspell/affixmgr.cxx
            src/hunspell/csutil.cxx
            src/hunspell/dictmgr.cxx
            src/hunspell/hashmgr.cxx
            src/hunspell/hunspell.cxx
            src/hunspell/phonet.cxx
            src/hunspell/replist.cxx
            src/hunspell/suggestmgr.cxx
            src/hunspell/utf_info.cxx
            src/hunspell/filemgr.cxx
            src/hunspell/hunzip.cxx)
endif()


# include(src/qcodeedit/qcodeedit.pri)

include_directories(src/qcodeedit/lib src/qcodeedit/lib/document src/qcodeedit/lib/widgets src/qcodeedit/lib/qnfa)
set(HEADERS ${HEADERS}
        src/qcodeedit/lib/qce-config.h
        src/qcodeedit/lib/qeditor.h
        src/qcodeedit/lib/qeditorfactory.h
        src/qcodeedit/lib/qcodeedit.h
        src/qcodeedit/lib/qpanellayout.h
        src/qcodeedit/lib/qformatfactory.h
        src/qcodeedit/lib/qformatscheme.h
        src/qcodeedit/lib/qlinemarksinfocenter.h
        src/qcodeedit/lib/qreliablefilewatch.h
        src/qcodeedit/lib/qeditorinputbinding.h
        src/qcodeedit/lib/qeditorinputbindinginterface.h
        src/qcodeedit/lib/qformat.h
        src/qcodeedit/lib/document/qdocument.h
        src/qcodeedit/lib/document/qdocument_p.h
        src/qcodeedit/lib/document/qdocumentcommand.h
        src/qcodeedit/lib/document/qdocumentcursor.h
        src/qcodeedit/lib/document/qdocumentline.h
        src/qcodeedit/lib/document/qdocumentsearch.h
        src/qcodeedit/lib/qcodecompletionengine.h
        src/qcodeedit/lib/qlanguagedefinition.h
        src/qcodeedit/lib/qlanguagefactory.h
        src/qcodeedit/lib/widgets/qpanel.h
        src/qcodeedit/lib/widgets/qlinenumberpanel.h
        src/qcodeedit/lib/widgets/qlinemarkpanel.h
        src/qcodeedit/lib/widgets/qlinechangepanel.h
        src/qcodeedit/lib/widgets/qfoldpanel.h
        src/qcodeedit/lib/widgets/qstatuspanel.h
        src/qcodeedit/lib/widgets/qsearchreplacepanel.h
        src/qcodeedit/lib/widgets/qgotolinedialog.h
        src/qcodeedit/lib/widgets/qgotolinepanel.h
        src/qcodeedit/lib/widgets/qeditconfig.h
        src/qcodeedit/lib/widgets/qformatconfig.h
        src/qcodeedit/lib/widgets/qsimplecolorpicker.h
        src/qcodeedit/lib/widgets/qcalltip.h)
set(SOURCES ${SOURCES}
        src/qcodeedit/lib/qeditor.cpp
        src/qcodeedit/lib/qeditorfactory.cpp
        src/qcodeedit/lib/qcodeedit.cpp
        src/qcodeedit/lib/qpanellayout.cpp
        src/qcodeedit/lib/qformatscheme.cpp
        src/qcodeedit/lib/qlinemarksinfocenter.cpp
        src/qcodeedit/lib/qreliablefilewatch.cpp
        src/qcodeedit/lib/qeditorinputbinding.cpp
        src/qcodeedit/lib/qformat.cpp
        src/qcodeedit/lib/document/qdocument.cpp
        src/qcodeedit/lib/document/qdocumentcommand.cpp
        src/qcodeedit/lib/document/qdocumentcursor.cpp
        src/qcodeedit/lib/document/qdocumentcursor_p.h
        src/qcodeedit/lib/document/qdocumentline.cpp
        src/qcodeedit/lib/document/qdocumentline_p.h
        src/qcodeedit/lib/document/qdocumentsearch.cpp
        src/qcodeedit/lib/qcodecompletionengine.cpp
        src/qcodeedit/lib/qlanguagedefinition.cpp
        src/qcodeedit/lib/qlanguagefactory.cpp
        src/qcodeedit/lib/widgets/qpanel.cpp
        src/qcodeedit/lib/widgets/qlinenumberpanel.cpp
        src/qcodeedit/lib/widgets/qlinemarkpanel.cpp
        src/qcodeedit/lib/widgets/qlinechangepanel.cpp
        src/qcodeedit/lib/widgets/qfoldpanel.cpp
        src/qcodeedit/lib/widgets/qstatuspanel.cpp
        src/qcodeedit/lib/widgets/qsearchreplacepanel.cpp
        src/qcodeedit/lib/widgets/qgotolinedialog.cpp
        src/qcodeedit/lib/widgets/qgotolinepanel.cpp
        src/qcodeedit/lib/widgets/qeditconfig.cpp
        src/qcodeedit/lib/widgets/qformatconfig.cpp
        src/qcodeedit/lib/widgets/qsimplecolorpicker.cpp
        src/qcodeedit/lib/widgets/qcalltip.cpp)
set(FORMS ${FORMS}
        src/qcodeedit/lib/widgets/gotoline.ui
        src/qcodeedit/lib/widgets/gotolinedialog.ui
        src/qcodeedit/lib/widgets/editconfig.ui
        src/qcodeedit/lib/widgets/formatconfig.ui)
target_compile_definitions(texstudio_interface INTERFACE  QNFA_BUILD)
set(HEADERS ${HEADERS}
        src/qcodeedit/lib/qnfa/qnfa.h
        src/qcodeedit/lib/qnfa/qnfadefinition.h
        src/qcodeedit/lib/qnfa/light_vector.h
        src/qcodeedit/lib/qnfa/xml2qnfa.h)
set(SOURCES ${SOURCES}
        src/qcodeedit/lib/qnfa/qnfa.cpp
        src/qcodeedit/lib/qnfa/qnfadefinition.cpp
        src/qcodeedit/lib/qnfa/xml2qnfa.cpp)

# include(src/latexparser/latexparser.pri)
include_directories(src/latexparser)
set(HEADERS ${HEADERS}
        src/latexparser/argumentlist.h
        src/latexparser/latextokens.h
        src/latexparser/latexparser.h
        src/latexparser/latexparsing.h
        src/latexparser/latexreader.h
        src/latexparser/commanddescription.h)
set(SOURCES ${SOURCES}
        src/latexparser/argumentlist.cpp
        src/latexparser/latextokens.cpp
        src/latexparser/latexparser.cpp
        src/latexparser/latexparsing.cpp
        src/latexparser/latexreader.cpp
        src/latexparser/commanddescription.cpp)

# include(src/symbolpanel/symbolpanel.pri)
include_directories(src/symbolpanel)
set(HEADERS ${HEADERS}
        src/symbolpanel/proxymodels.h
        src/symbolpanel/symbollistmodel.h
        src/symbolpanel/symbollistview.h
        src/symbolpanel/symbolwidget.h)
set(SOURCES ${SOURCES}
        src/symbolpanel/proxymodels.cpp
        src/symbolpanel/symbollistmodel.cpp
        src/symbolpanel/symbollistview.cpp
        src/symbolpanel/symbolwidget.cpp)

if (USE_SYSTEM_QUAZIP)
    if (USE_QT5)
        find_package(QuaZip5 REQUIRED)
        include_directories(${QUAZIP_INCLUDE_DIRS})
    else()
        find_package(QuaZip REQUIRED)
        include_directories(${QUAZIP_INCLUDE_DIRS})
    endif()
    target_link_libraries(texstudio_interface INTERFACE ${QUAZIP_LIBRARIES})
else()
    target_compile_definitions(texstudio_interface INTERFACE  QUAZIP_STATIC)
    # include(src/quazip/quazip/quazip.pri)
endif()

# include(src/pdfviewer/pdfviewer.pri)
include_directories(src/pdfviewer)
# include(synctex/synctex.pri)
include_directories(src/pdfviewer/synctex)
set(HEADERS ${HEADERS}
        src/pdfviewer/synctex/synctex_parser.h
        src/pdfviewer/synctex/synctex_parser_utils.h
        src/pdfviewer/synctex/synctex_parser_advanced.h
        src/pdfviewer/synctex/synctex_version.h)
set(SOURCES ${SOURCES}
        src/pdfviewer/synctex/synctex_parser.c
        src/pdfviewer/synctex/synctex_parser_utils.c)


set(HEADERS ${HEADERS}
        src/pdfviewer/PDFDocument.h
        src/pdfviewer/PDFDocks.h
        src/pdfviewer/pdfrenderengine.h
        src/pdfviewer/pdfrendermanager.h
        src/pdfviewer/PDFDocument_config.h
        src/pdfviewer/pdfannotationdlg.h
        src/pdfviewer/pdfannotation.h
        src/pdfviewer/qsynctex.h)
set(SOURCES ${SOURCES}
        src/pdfviewer/PDFDocument.cpp
        src/pdfviewer/PDFDocks.cpp
        src/pdfviewer/pdfrenderengine.cpp
        src/pdfviewer/pdfrendermanager.cpp
        src/pdfviewer/pdfannotationdlg.cpp
        src/pdfviewer/pdfannotation.cpp
        src/pdfviewer/qsynctex.cpp)
set(FORMS ${FORMS}
        src/pdfviewer/pdfannotationdlg.ui)

if(NO_POPPLER_PREVIEW)
    target_compile_definitions(texstudio_interface INTERFACE  NO_POPPLER_PREVIEW)
else()
    if(WIN32)
        if(USE_QT5)
            include_directories(src/pdfviewer/include_win32_qt5)
        else()
            include_directories(src/pdfviewer/include_win32)
        endif()
        target_compile_definitions(texstudio_interface INTERFACE  HAS_POPPLER_24)
        target_compile_definitions(texstudio_interface INTERFACE  HAS_POPPLER_31)
    else()
        find_package(ECM 5.19 REQUIRED NOMODULE)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
        if(USE_QT5)
            find_package(Poppler COMPONENTS Qt5 REQUIRED)
            target_link_libraries(texstudio_interface INTERFACE Poppler::Qt5) # Poppler::Core

        else()
            find_library(Poppler COMPONENTS Qt4 REQUIRED)
            target_link_libraries(texstudio_interface INTERFACE Poppler::Qt4) # Poppler::Core
        endif()
        if (${Poppler_VERSION} GREATER 0.24)
            target_compile_definitions(texstudio_interface INTERFACE  HAS_POPPLER_24)
        endif()
        if (${Poppler_VERSION} GREATER 0.31)
            target_compile_definitions(texstudio_interface INTERFACE  HAS_POPPLER_31)
        endif()
    endif()
endif()

IF(USE_TESTS) #TODO
    enable_testing(true)

    if (USE_QT5)
        find_package(Qt5 COMPONENTS Test REQUIRED)
        target_link_libraries(texstudio_interface INTERFACE Qt5::Test)
    else()
        find_package(Qt4 COMPONENTS Test REQUIRED)
    endif()

    set(HEADERS ${HEADERS}
            src/tests/qsearchreplacepanel_t.h
            src/tests/updatechecker_t.h
            src/tests/qdocumentcursor_t.h
            src/tests/qdocumentline_t.h
            src/tests/qdocumentsearch_t.h
            src/tests/codesnippet_t.h
            src/tests/latexcompleter_t.h
            src/tests/latexeditorview_bm.h
            src/tests/latexeditorview_t.h
            src/tests/latexoutputfilter_t.h
            src/tests/latexparser_t.h
            src/tests/latexparsing_t.h
            src/tests/latexstyleparser_t.h
            src/tests/scriptengine_t.h
            src/tests/qeditor_t.h
            src/tests/buildmanager_t.h
            src/tests/tablemanipulation_t.h
            src/tests/smallUsefulFunctions_t.h
            src/tests/utilsui_t.h
            src/tests/utilsversion_t.h
            src/tests/encoding_t.h
            src/tests/help_t.h
            src/tests/syntaxcheck_t.h
            src/tests/qcetestutil.h
            src/tests/testmanager.h
            src/tests/testutil.h
            src/tests/usermacro_t.h
            src/tests/structureview_t.h)
    set(SOURCES ${SOURCES}
            src/tests/codesnippet_t.cpp
            src/tests/encoding_t.cpp
            src/tests/latexcompleter_t.cpp
            src/tests/latexeditorview_bm.cpp
            src/tests/latexeditorview_t.cpp
            src/tests/latexoutputfilter_t.cpp
            src/tests/latexparser_t.cpp
            src/tests/latexparsing_t.cpp
            src/tests/qcetestutil.cpp
            src/tests/qdocumentcursor_t.cpp
            src/tests/qdocumentline_t.cpp
            src/tests/qdocumentsearch_t.cpp
            src/tests/qeditor_t.cpp
            src/tests/qsearchreplacepanel_t.cpp
            src/tests/scriptengine_t.cpp
            src/tests/smallUsefulFunctions_t.cpp
            src/tests/structureview_t.cpp
            src/tests/syntaxcheck_t.cpp
            src/tests/tablemanipulation_t.cpp
            src/tests/usermacro_t.cpp
            src/tests/testmanager.cpp
            src/tests/testutil.cpp)
else()
    target_compile_definitions(texstudio_interface INTERFACE  NO_TESTS)
endif()

if(NO_CRASH_HANDLER)
    target_compile_definitions(texstudio_interface INTERFACE  NO_CRASH_HANDLER)
endif()

## TODO not git
if(WIN32)
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/src/git_revision.cpp
            WORKING_DIR ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_SOURCE_DIR}/git_revision.bat ${CMAKE_CXX_COMPILER} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}
    )
else()
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/src/git_revision.cpp ${CMAKE_CURRENT_BINARY_DIR}/git_revision.o
            WORKING_DIR ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_SOURCE_DIR}/git_revision.sh ${CMAKE_CXX_COMPILER} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}
    )
endif()

set(SOURCES ${SOURCES}
        src/git_revision.cpp)

if(MSVC)
    target_compile_definitions(texstudio_interface INTERFACE  _CRT_SECURE_NO_WARNINGS)
endif()


if (USE_QT5)
    qt5_wrap_ui(UI_HEADERS ${FORMS})
    qt5_wrap_cpp(MOC_SOURCES ${SOURCES} OPTIONS -DQT_VERSION=0x050000)
    qt5_wrap_cpp(MOC_HEADERS ${HEADERS} OPTIONS -DQT_VERSION=0x050000) # https://bugreports.qt.io/browse/QTBUG-51028
    qt5_add_resources(RCC_SOURCES ${RESOURCES})
else()
    QT4_WRAP_UI(UI_HEADERS ${FORMS})
endif()
target_include_directories(texstudio_interface INTERFACE ${CMAKE_CURRENT_BINARY_DIR}) # https://gitlab.kitware.com/cmake/cmake/issues/17456

if(NOT MSVC)
    set(WARNINGS_FLAGS -Wall -Wextra -Winit-self -Wmissing-include-dirs)
    set(WARNINGS_FLAGS ${WARNINGS_FLAGS} -Wtrigraphs -Wunused -Wunknown-pragmas -Wundef -Wpointer-arith)
    set(WARNINGS_FLAGS ${WARNINGS_FLAGS} -Wwrite-strings -Wempty-body -Wsign-compare -Waddress -Winline)
    target_compile_options(texstudio_interface INTERFACE "$<$<CONFIG:DEBUG>:${WARNINGS_FLAGS}>")
    if(UNIX)
        target_link_options(texstudio_interface INTERFACE -rdynamic)
    else()
        target_compile_options(texstudio_interface INTERFACE -gstabs -g)
    endif()
    if (USE_ASAN)
        target_compile_options(texstudio_interface INTERFACE -fsanitize=address -fno-omit-frame-pointer -g)
    endif()
endif()

if (USE_IPO)
    include(CheckIPOSupported)
    # Optional IPO. Do not use IPO if it's not supported by compiler.
    check_ipo_supported(RESULT HAS_IPO OUTPUT IPO_CHECK_RESULT)
    if(HAS_IPO)
        set_property(TARGET texstudio_interface PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(WARNING "IPO is not supported: ${IPO_CHECK_RESULT}")
    endif()
endif()


add_library(texstudio_object OBJECT ${SOURCES} ${UI_HEADERS} ${RCC_SOURCES} ${MOC_SOURCES} ${MOC_HEADERS})
set_property(TARGET texstudio_object PROPERTY CXX_STANDARD 11)
target_link_libraries(texstudio_object texstudio_interface)

add_library(texstudio_static STATIC $<TARGET_OBJECTS:texstudio_object>)
add_library(texstudio_shared SHARED $<TARGET_OBJECTS:texstudio_object>)

add_executable(texstudio $<TARGET_OBJECTS:texstudio_object> src/main.cpp)
target_link_libraries(texstudio texstudio_interface)
target_link_libraries(texstudio texstudio_static)

if (TRUE AND WIN32) # TODO not 4.3
    target_compile_definitions(texstudio_shared PUBLIC QT_QTSINGLECOREAPPLICATION_EXPORT=__declspec(dllexport))
endif()
