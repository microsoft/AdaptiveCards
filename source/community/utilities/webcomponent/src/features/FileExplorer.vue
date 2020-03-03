<template>
  <modal
    width="800px"
    :loading="loading"
    @dismiss="$emit('dismiss')"
  >
    <template v-slot:header>
      <div>
        <div style="display: flex; align-items: center; color: #BBB;">
          <img
            src="//cdn.teamwork.com/images/pages/settings/dropbox_logo_150x40.png"
            alt="dropbox logo"
          >
          <span
            :style="{
              fontSize: '20px',
              fontWeight: 'lighter'}"
          >
            — Choose files
            {{ selected.length>0 ?
              ` · ${selected.length} file${selected.length>1?'s':''} selected`
              : ''
            }}
          </span>
        </div>
        <div :style="{display:'flex'}">
          <div :style="{flex:1}" />
          <tw-button
            color="primary"
            icon="cloud-upload-alt"
            label="Upload"
            @click="$refs.uploadfile.click()"
          />
          <input
            v-if="!loading"
            ref="uploadfile"
            style="display:none"
            type="file"
            @change="fileUpload"
          >
        </div>
        <div :style="{height:'8px'}" />
        <div :style="{display:'flex'}">
          <div :style="{flex:1}" />
          <div :style="{display:'flex'}">
            <span :style="{width: '12px', marginRight: '-20px', marginTop: '7px', zIndex:1}">
              <font-awesome-icon icon="search" />
            </span>
            <input
              v-model="searchTerm"
              :style="{
                borderRadius: '5px',
                border:'1px solid rgba(0,0,0,0.1)',
                padding: '4px 4px 4px 25px',
                fontSize:'13px',
                fontFamily: '\'Open Sans\', \'Helvetica Neue\', Helvetica, Arial, \'sans-serif\''
              }"
              type="text"
              placeholder="Search For..."
              @keyup.enter="search"
            >
          </div>
        </div>
        <div>
          <a
            href="javascript:;"
            @click="selectParentFolder()"
          >Dropbox</a>
          <span>»</span>
          <span
            v-for="(item, i) in stack"
            :key="item.id"
          >
            <span v-if="i < stack.length-1">
              <a
                href="javascript:;"
                @click="selectParentFolder(item.id)"
              >{{ item.name }}</a>
              <span style="padding:3px">»</span>
            </span>
            <span v-else>{{ item.name }}</span>
          </span>
        </div>
      </div>
    </template>

    <div style="margin:8px">
      <table style="width:100%">
        <thead>
          <tr style="text-align:left; height: 30px; vertical-align: top;">
            <th style="display:flex">
              File Name
              <div style="width:10px; margin-left: 10px;">
                <font-awesome-icon icon="caret-up" />
              </div>
            </th>
            <th>Size</th>
            <th>Modified</th>
          </tr>
        </thead>
        <tbody :style="{ opacity: loading ? 0.5 : 1}">
          <tr v-if="stack.length>0">
            <td>
              <a
                href="javascript:;"
                :style="{
                  paddingLeft: '20px',
                  background:
                    'transparent url(\'//cdn.teamwork.com/images/integrations/dropbox/icons/16x16/up.gif\') 0 0 no-repeat'
                }"
                @click="selectParentFolder(stack[stack.length-2] && stack[stack.length-2].id)"
              >Parent Folder</a>
            </td>
            <td colspan="2" />
          </tr>

          <tr v-if="items.length === 0">
            <td
              colspan="3"
              style="text-align:center; height: 100px"
            >
              This folder is empty
            </td>
          </tr>

          <tr
            v-for="item in formattedItems"
            :key="item.id"
          >
            <td>
              <input
                v-if="!item.isDirectory"
                :checked="selected.includes(item.id)"
                type="checkbox"
                @click="toggle(item)"
              >
              <a
                href="javascript:;"
                :style="{
                  paddingLeft: '20px',
                  background:
                    'transparent url(\'//cdn.teamwork.com/images/integrations/dropbox/icons/16x16/'
                    + (item.isDirectory ? 'folder':'page_white') + '.gif\') 0 0 no-repeat'
                }"
                @click="item.isDirectory ? selectChildFolder(item) : toggle(item)"
              >{{ item.name }}</a>
            </td>
            <td>{{ item.isDirectory ? '':item.size }}</td>
            <td>{{ item.isDirectory ? '':item.modified }}</td>
          </tr>
        </tbody>
      </table>
      <div
        v-if="hasMore"
        style="display: flex;"
        :style="{ opacity: loading ? 0.5 : 1}"
      >
        <div style="flex:1" />
        <tw-button
          label="Load more items"
          @click="load(currentFolderId, continuationToken)"
        />
        <div style="flex:1" />
      </div>
    </div>
    <template v-slot:footer>
      <div style="display:flex">
        <tw-button
          label="Close"
          @click="$emit('dismiss')"
        />
        <div style="flex:1; minWidth: 80px;" />
        <tw-button
          color="secondary"
          icon="folder"
          label="Create Folder"
          @click="createFolderModalShow=true"
        />
        <tw-button
          color="secondary"
          icon="check-square"
          label="Select All"
          @click="selectAll"
        />
        <tw-button
          v-if="selected.length>0"
          color="secondary"
          icon="square"
          label="Clear selection"
          @click="selected=[]"
        />
        <tw-button
          :disabled="selected.length===0"
          color="primary"
          label="Link-in Selected Files"
          @click="$emit('link-files', {selected})"
        />
      </div>
    </template>
    <CreateFolder
      v-if="createFolderModalShow"
      :parent-folder-id="currentFolderId"
      @dismiss="createFolderModalShow=false"
      @folder-created="refresh"
    />
  </modal>
</template>

<script>
import prettyBytes from 'pretty-bytes';
import api from '../api';
import CreateFolder from './CreateFolder.vue';

export default {
  components: {
    CreateFolder,
  },
  props: {},
  data() {
    return {
      loading: false,
      items: [],
      stack: [],
      selected: [],
      createFolderModalShow: false,
      hasMore: false,
      continuationToken: undefined,
      fileupload: undefined,
      searchTerm: '',
    };
  },
  computed: {
    currentFolderId() {
      return this.stack[this.stack.length - 1]?.id;
    },
    formattedItems() {
      return this.items.map((item) => ({
        ...item,
        size: prettyBytes(item.size),
        modified: new Date(item.modified).toLocaleString(),
      }));
    },
  },
  created() {
    this.load();
  },
  methods: {
    async selectChildFolder(item) {
      if (this.loading) return;
      await this.load(item.id);
      this.stack.push(item);
    },
    async selectParentFolder(folderId = '') {
      if (this.loading) return;
      await this.load(folderId);
      const index = this.stack.findIndex((item) => item.id === folderId);
      this.stack = this.stack.slice(0, index + 1);
    },
    selectAll() {
      this.selected = [
        ...new Set([
          ...this.selected,
          ...this.items.filter((i) => !i.isDirectory).map((i) => i.id),
        ]),
      ];
    },
    toggle({ id }) {
      if (this.selected.includes(id)) {
        this.selected = this.selected.filter((f) => f !== id);
      } else {
        this.selected.push(id);
      }
    },
    async fileUpload() {
      try {
        this.loading = true;
        await api.fileUpload(
          this.currentFolderId,
          this.$refs.uploadfile.files[0],
        );
      } catch (e) {
        console.error(e); // eslint-disable-line no-console
      } finally {
        this.loading = false;
        this.refresh();
      }
    },
    async load(folderId = '', continuationToken = '') {
      try {
        this.loading = true;
        const result = await api.fetchItems(folderId, continuationToken);
        const items = result?.contents;
        this.items = continuationToken ? [...this.items, ...items] : items;
        this.hasMore = result?.hasMore;
        this.continuationToken = result?.cursor;
      } catch (e) {
        console.error(e); // eslint-disable-line no-console
      } finally {
        this.loading = false;
      }
    },
    async refresh() {
      await this.load(this.currentFolderId);
    },
    async search() {
      if (this.searchTerm === '') {
        await this.load(this.currentFolderId);
      } else {
        try {
          this.loading = true;
          this.hasMore = false;
          this.continuationToken = '';
          const result = await api.search(this.searchTerm);
          this.items = result?.contents;
        } catch (e) {
          console.error(e); // eslint-disable-line no-console
        } finally {
          this.loading = false;
        }
      }
    },
  },
};
</script>
